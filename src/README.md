# DP-Week2-Task2 — Deicide: Core Loop Architecture

Game berbasis kartu terinspirasi dari Balatro, menggunakan karakter dari dunia **Deicide**. Fokus task ini adalah arsitektur: memisahkan **invariant** dari **mutable** dalam sebuah game loop nyata.

---

## Cara Build & Jalankan

```bash
g++ -std=c++17 main.cpp BondScaling.cpp -o deicide
.\deicide.exe
```

> Pastikan semua file `.h`, `BondScaling.cpp`, dan `main.cpp` berada dalam **satu folder yang sama**.

---

## Struktur File

```
Task2/
├── main.cpp                  # Entry point — merakit semua komponen
│
├── [INVARIANT]
│   └── GameSession.h         # Game loop controller — urutan fase dikunci di sini
│
├── [INTERFACE — kontrak mutable]
│   ├── ICard.h               # Interface kartu (Prototype pattern)
│   ├── IBondRule.h           # Interface bond/modifier
│   ├── IScoringRule.h        # Interface scoring
│   ├── IShopSystem.h         # Interface shop + ShowRegistry
│   └── IWinCondition.h       # Interface win/lose condition
│
├── [IMPLEMENTASI KONKRIT — mutable]
│   ├── BaseCard.h            # Implementasi kartu dasar
│   ├── CardRegistry.h        # Factory + registry 13 prototype kartu
│   ├── Deck.h                # Menarik kartu dari registry
│   ├── BondScaling.h         # Deklarasi nilai buff semua bond
│   ├── BondScaling.cpp       # Definisi nilai awal (satu tempat, tidak duplikat)
│   ├── ModifierFactory.h     # 15 bond class + upgrade + ShowBondRegistry
│   ├── DeicideScoringRule.h  # Scoring: totalJourney x totalCycle
│   ├── TitanShopSystem.h     # Kremnos Pack + Okhema Pack + ShowRegistry
│   └── StandardWinCondition.h# Win: score >= goal; goal x1.5 tiap round
```

---

## Step 1 — Core Loop Game

Urutan core loop yang terkunci dalam `GameSession::Start()`:

```
1.  Draw hand (8 kartu dari deck)
2.  Tampilkan hand ke player
3.  Player memilih aksi: Play / Discard / View
4.  [Jika Play]
    a. Player pilih kartu (maks 4)
    b. Cek dan terapkan semua Bond yang aktif
    c. Hitung score: totalJourney × totalCycle
    d. Update total score round
    e. Refill hand
5.  [Jika Discard] buang kartu, draw pengganti (habiskan 1 aksi)
6.  [Jika View] tampilkan registry (gratis, tidak habiskan aksi)
7.  Ulangi langkah 2–6 selama action points > 0 dan score belum mencapai goal
8.  Cek hasil: WIN jika score >= goal, GAME OVER jika tidak
9.  [Jika WIN] buka Shop (upgrade kartu atau bond), lanjut ke round berikutnya
10. Repeat dari langkah 1 dengan goal lebih tinggi
```

---

## Step 2 — Invariant

### Langkah yang tidak boleh berubah urutannya

| Urutan | Fase | Alasan |
|--------|------|--------|
| 1 | Draw hand | Kartu harus ada sebelum aksi apapun bisa dilakukan |
| 2 | Tampilkan hand | Player harus tahu isi hand sebelum memilih |
| 3 | Terima input player | Input harus diterima sebelum sistem menghitung apapun |
| 4a | Apply bond | Bond hanya berlaku pada kartu yang sudah dipilih player, bukan seluruh hand |
| 4b | Compute score | Score dihitung setelah bond diterapkan; jika terbalik, efek bond tidak masuk score |
| 4c | Update score | Score diperbarui setelah dihitung, tidak boleh sebelum atau bersamaan |
| 8 | Cek win/lose | Evaluasi hanya setelah semua aksi selesai dan score final diketahui |
| 9 | Shop | Shop hanya terbuka jika player menang, tidak sebelumnya |
| 10 | Advance round | Round baru dimulai setelah shop selesai |

### Komponen yang wajib selalu ada

- `GameSession` — penjaga urutan fase, tidak boleh dimodifikasi
- `ICard` + `Deck` + `CardRegistry` — tanpa kartu, tidak ada game
- `IBondRule` — tanpa modifier, tidak ada sistem buff
- `IScoringRule` — tanpa scoring, tidak ada cara menentukan hasil
- `IWinCondition` — tanpa kondisi menang/kalah, game tidak bisa berakhir
- `IShopSystem` — tanpa shop, tidak ada progression antar round

### Yang rusak jika urutan berubah

Jika bond diterapkan sebelum kartu dipilih → semua kartu di hand ter-buff, bukan hanya yang dimainkan. Jika score dihitung sebelum bond → efek bond tidak pernah masuk ke score. Jika shop dibuka sebelum cek hasil → player bisa upgrade meski kalah, menghilangkan seluruh konsekuensi kekalahan.

---

## Step 3 — Mutable Elements

Ada dua jenis mutable dalam sistem ini, keduanya **tidak menyentuh `GameSession`**:

### Mutable Arsitektural — komponen yang di-inject ke GameSession

| Komponen | Bisa Diganti Dengan | Cara |
|---|---|---|
| `IBondRule` (15 bond classes) | Bond baru tambah class baru, bond lama hapus dari vector | Edit daftar di `main.cpp` saja |
| `IScoringRule` (DeicideScoringRule) | Rumus scoring lain, misal `Journey + Cycle` | Buat class baru, inject di `main.cpp` |
| `IShopSystem` (TitanShopSystem) | Toko dengan mekanisme berbeda | Buat class baru, inject di `main.cpp` |
| `IWinCondition` (StandardWinCondition) | Survival mode, time limit, dll | Buat class baru, inject di `main.cpp` |

Keempat komponen ini bersifat mutable karena `GameSession` hanya mengenal **interface**-nya, bukan implementasinya. Mengganti implementasi tidak memerlukan perubahan pada `GameSession`.

### Mutable Data — nilai yang berubah saat runtime

| Data | Mekanisme Perubahan |
|---|---|
| `BondScaling` (nilai buff bond) | Naik via Okhema Pack di `TitanShopSystem` setiap round |
| Prototype kartu (Journey & Cycle) | Naik via Kremnos Pack di `TitanShopSystem` setiap round |

Nilai-nilai ini berubah **selama game berjalan** melalui sistem upgrade di shop, bukan melalui penggantian class. Ini berbeda dari mutable arsitektural — strukturnya tetap, hanya datanya yang berubah.

---

## Step 4 — Implementasi C++ Skeleton

Struktur inti `GameSession` yang mencerminkan invariant:

```cpp
class GameSession {
private:
    // Semua logika di-inject — GameSession tidak tahu implementasinya
    std::vector<IBondRule*>  bondRules;
    IScoringRule*            scoringRule;
    IShopSystem*             shopSystem;
    IWinCondition*           winCondition;

public:
    void Start() {
        while (isRunning) {
            Phase_DrawHand();          // Fase 1
            while (actionPoints > 0) {
                DisplayHand();         // Fase 2
                Phase_PlayerAction();  // Fase 3 → 4a → 4b → 4c
            }
            Phase_CheckResult();       // Fase 8
            Phase_Shop();              // Fase 9 (jika menang)
            Phase_AdvanceRound();      // Fase 10
        }
    }
};
```

`GameSession` tidak include `ModifierFactory.h`. Ia tidak tahu bond apa yang ada, bagaimana scoring dihitung, atau seperti apa toko bekerja.

---

## Daftar Kartu & Faksi

| Kartu | Faksi | Journey | Cycle |
|-------|-------|---------|-------|
| Janus | TITAN FATE | 1 | 6 |
| Talanton | TITAN FATE | 5 | 4 |
| Oronyx | TITAN FATE | 15 | 3 |
| Georios | TITAN FOUNDATION | 75 | 1 |
| Phagousa | TITAN FOUNDATION | 50 | 1 |
| Aquila | TITAN FOUNDATION | 40 | 2 |
| Kephale | TITAN CREATION | 100 | 1 |
| Cerces | TITAN CREATION | 5 | 6 |
| Mnestia | TITAN CREATION | 40 | 3 |
| Nikador | TITAN CALAMITY | 80 | 1 |
| Thanatos | TITAN CALAMITY | 40 | 2 |
| Zegreus | TITAN CALAMITY | 10 | 4 |
| Demiurge | SPECIAL | 100 | 6 |

**Rumus Score:** `totalJourney × totalCycle`

---

## Daftar Bond

**Faction Bonds** (aktif jika ≥2 kartu dari faksi yang sama):

| Bond | Kartu | Efek Awal |
|------|-------|-----------|
| TITAN FATE | Janus, Talanton, Oronyx | +2 Cycle/kartu untuk kartu FATE |
| TITAN FOUNDATION | Georios, Phagousa, Aquila | +20 Journey/kartu untuk ALL |
| TITAN CALAMITY | Nikador, Thanatos, Zegreus | +30J +2C/kartu untuk kartu CALAMITY |
| TITAN CREATION | Kephale, Cerces, Mnestia | +10J +1C/kartu untuk ALL |

**Special Combo Bonds:**

| Bond | Syarat | Efek Awal |
|------|--------|-----------|
| Grove Academy | Cerces + Aquila | +4 Cycle ALL |
| Okhema Elders | Janus + Mnestia | +4 Cycle ALL |
| Dux Kaisar | Phagousa + Talanton | +40 Journey ALL |
| Side Nameless | Oronyx + Georios | +20J +2C ALL |
| Mother & Daughter | Mnestia + Zegreus | +20J +2C ALL |
| Cycle Beginning | Demiurge + Kephale | +500 Journey Kephale |
| Child of Time | Oronyx + Demiurge | +10 Journey Kephale/Nikador |
| War General | Aquila + Nikador | +100 Journey Kephale/Nikador |
| Heated Rivalry | Kephale + Nikador | +100 Journey keduanya |
| Three Nameless | Georios + Oronyx + Kephale | +100 Journey tiga kartu |
| **DEICIDE SYMPHONY** | Oronyx + Georios + Demiurge + Kephale | **×3 Semua Stat** |

Semua nilai buff di atas dapat ditingkatkan lewat **Okhema Pack** di shop.

---

## Refleksi

### 1. Apa invariant structure dalam game ini?

Invariant adalah **urutan fase** yang dikunci di dalam `GameSession::Start()`. Setiap round harus selalu menjalankan fase dalam urutan yang sama: draw hand → tampilkan → input player → apply bond → hitung score → update score → cek hasil → shop → advance round. `GameSession` adalah satu-satunya class yang menentukan *kapan* setiap fase terjadi. Ia tidak tahu *bagaimana* scoring dihitung, bond apa yang aktif, toko seperti apa, atau kondisi menang seperti apa — semuanya diserahkan ke implementasi yang di-inject dari luar. Selama `GameSession` tidak diubah, urutan fase terjaga.

### 2. Bagian mana yang mutable?

Ada dua lapisan mutable. Lapisan pertama adalah **mutable arsitektural**: empat interface (`IBondRule`, `IScoringRule`, `IShopSystem`, `IWinCondition`) beserta implementasinya bisa diganti sepenuhnya tanpa menyentuh `GameSession` — cukup inject implementasi berbeda di `main.cpp`. Lapisan kedua adalah **mutable data**: nilai-nilai numerik dalam `BondScaling` (buff bond) dan prototype kartu (`CardRegistry`) berubah selama game berjalan melalui sistem upgrade di shop. Keduanya mutable, tapi dalam konteks yang berbeda.

### 3. Jika ingin menambah fitur baru, class mana yang berubah?

Bergantung pada jenis fiturnya. Untuk bond baru: buat class turunan `IBondRule`, daftarkan di vector di `main.cpp`. Untuk rumus scoring baru: buat implementasi `IScoringRule` baru, inject di `main.cpp`. Untuk mekanik shop baru: modifikasi `TitanShopSystem` atau buat implementasi `IShopSystem` baru. Untuk kondisi menang berbeda: buat implementasi `IWinCondition` baru. Dalam semua kasus, `GameSession` tidak perlu disentuh.

### 4. Jika urutan loop diubah, apa yang rusak?

Jika bond diterapkan sebelum kartu dipilih, seluruh hand akan ter-buff bukan hanya kartu yang dimainkan — ini merusak keseimbangan game secara fundamental karena player mendapat buff gratis setiap giliran. Jika score dihitung sebelum bond, efek semua bond tidak pernah terhitung dalam score sehingga seluruh sistem bond menjadi tidak berguna. Jika shop dibuka sebelum hasil round dicek, player bisa upgrade bahkan saat kalah sehingga tidak ada konsekuensi dari kekalahan. Urutan fase bukan sekadar konvensi — setiap fase bergantung secara langsung pada output fase sebelumnya.

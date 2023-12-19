//lumayan rapi
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>


using namespace std;

//mendeklarasikan struct apa saja yang akan di pakai
struct akun_user{
    string nama;
    string kode;
};
  
string dev1 = "     1. Abdullah Azam (2209106056)          ";
string dev2 = "     2. Ahmad  Nur Fauzan (2209106057)      ";
string dev3 = "     3. Muhammad Abdillah (2209106065)      ";
string dev4 = "     4. Tommy Chandra Gunawah (2209106068)  ";

string *ptr1 = &dev1;
string *ptr2 = &dev2;
string *ptr3 = &dev3;
string *ptr4 = &dev4;

struct detail_barang
{
    int harga;
    int jumlah;
};
struct barang
{
    string nama_barang;
    string jenis_barang;
    string satuan;
    struct detail_barang detail_barangnya;
};

struct datatransaksi
{
    string namapembeli;
    string namabarang;
    int hargasatuan;
    int jumlahbeli;
    int hargatotal;
    int jumlahbayar;
    int kembalian;
};

//deklarasiakn array apa saja yg akan di pakai
datatransaksi transaksi[100];
int jumlah_transaksi = 0;

barang data_barang[500];
int jumlah_barang = 0;
int n = sizeof(data_barang) / sizeof(data_barang[0]);
akun_user akun[100];
int jumlah_akun = 0;

string pilih;

int menu;
//untuk mencatat siapa user yang sedang login
string username;

int val_int(string perintah) {
    int num;
    string coba;
    while (true)
    {
        cout << perintah; fflush(stdin); getline(cin, coba);
        stringstream ss(coba);
        if (ss >> num && num >= 1) {
            break;
        } else {
            cout << "======== Input tidak sesuai, silakan coba lagi ========" << endl;
        }
    }
    return num;
}
// untuk memvalidasi apakan akan membatalkan transaksi atau tidak
string val_yatdk(string perintah) {
    string coba;
    while (true)
    {
        cout << perintah; fflush(stdin); getline(cin, coba);
        if (coba == "y" or coba == "n") {
            // cout << "inputan benar" << endl;
            break;
        } else {
            cout << "Input y/n, silakan coba lagi." << endl;
        }
    }
    return coba;
}

bool menu_valid(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}  

//repl untuk singkron file csv dengan array dipakai setelah hapus dan edit
void repl_barang(){
	ofstream file;
    file.open("databarang.csv", ios::out | ios::trunc);
    for (int i = 0 ; i < jumlah_barang ; i++){
    	file << data_barang[i].nama_barang << ",";
        file << data_barang[i].jenis_barang << ",";
        file << data_barang[i].detail_barangnya.harga << ",";
        file << data_barang[i].detail_barangnya.jumlah << ",";
        file << data_barang[i].satuan << "\n";
	}
	file.close();
}

//untuk membaca file csv dari transaksi dan menambahnya ke array transaksi
void read_file_transaksi(){
    ifstream file;
    string data, namapembeli, namabarang, hargasatuan, jumlahbeli, hargatotal, jumlahbayar, kembalian;
    string str_hargasatuan, str_jumlahbeli, str_hargatotal, str_jumlahbayar, str_kembalian;
    int int_hargasatuan, int_jumlahbeli, int_hargatotal, int_jumlahbayar, int_kembaian;
    file.open("datatransaksi.csv", ios::in);
    if (file.is_open())
    {
        while (getline(file, data)){
            stringstream ter(data);

            getline(ter, namapembeli, ',');
            getline(ter, namabarang, ',');
            getline(ter, hargasatuan, ',');
            getline(ter, jumlahbeli, ',');
            getline(ter, hargatotal, ',');
            getline(ter, jumlahbayar, ',');
            getline(ter, kembalian, '\n');

            stringstream str_hargasatuan(hargasatuan);
            stringstream str_jumlahbeli(jumlahbeli);
            stringstream str_hargatotal(hargatotal);
            stringstream str_jumlahbayar(jumlahbayar);
            stringstream str_kembalian(kembalian);

            str_hargasatuan >> int_hargasatuan;
            str_jumlahbeli >> int_jumlahbeli;
            str_hargatotal >> int_hargatotal;
            str_jumlahbayar >> int_jumlahbayar;
            str_kembalian >> int_kembaian;

            transaksi[jumlah_transaksi].namapembeli = namapembeli;
            transaksi[jumlah_transaksi].namabarang = namabarang;
            transaksi[jumlah_transaksi].hargasatuan = int_hargasatuan;
            transaksi[jumlah_transaksi].jumlahbeli = int_jumlahbeli;
            transaksi[jumlah_transaksi].hargatotal = int_hargatotal;
            transaksi[jumlah_transaksi].jumlahbayar = int_jumlahbayar;
            transaksi[jumlah_transaksi].kembalian = int_kembaian;
            jumlah_transaksi++;

        }
    }
    file.close();
}

//untuk membaca file csv dari databarang dan menambahnya ke array data_barang

//untuk membaca file csv dari databarang dan menambahnya ke array data_barang
void read_file_barang(){
    ifstream file;
    string data,nama,jenis,harga,jumlah,str_harga,str_jumlah,satuan;
    int harga_int,jumlah_int;
    file.open("databarang.csv", ios::in);
    if (file.is_open())
    {
        while (getline(file, data))
        {
            stringstream bb(data);

            getline(bb, nama, ',');
            getline(bb, jenis, ',');
            getline(bb, harga, ',');
            getline(bb, jumlah, ',');
            getline(bb, satuan, '\n');

            stringstream str_harga(harga);
            stringstream str_jumlah(jumlah);

            str_harga >> harga_int;
            str_jumlah >> jumlah_int;

            data_barang[jumlah_barang].nama_barang = nama;
            data_barang[jumlah_barang].jenis_barang = jenis;
            data_barang[jumlah_barang].detail_barangnya.harga = harga_int;
            data_barang[jumlah_barang].detail_barangnya.jumlah = jumlah_int;
            data_barang[jumlah_barang].satuan = satuan;
            jumlah_barang = jumlah_barang + 1;
        }
    }
    file.close();
}


//untuk membaca file csv dari akun dan menambahnya ke array akun
void read_file_akun(){
	ifstream file;
	string data, nama, kode;
	file.open("dataakun.csv", ios::in);
	if (file.is_open()){
		while (getline(file, data)){
			stringstream ss(data);
			
			getline(ss, nama, ',');
			getline(ss, kode, '\n');
			
			akun[jumlah_akun].nama = nama;
			akun[jumlah_akun].kode = kode;
			jumlah_akun++;
		}
	}
	file.close();
}

void display_barang(){
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0 ; i < jumlah_barang ; i++)
    {
    int p=i+1;
    cout << "nomor         : " << p << endl;
    cout << "Nama          : " << data_barang[i].nama_barang << endl;
    cout << "jenis         : " << data_barang[i].jenis_barang << endl;
    cout << "harga         : " << data_barang[i].detail_barangnya.harga << endl;
    cout << "jumlah        : " << data_barang[i].detail_barangnya.jumlah << endl;
    cout << "satuan        : " << data_barang[i].satuan << endl;
    cout << "-------------------------------------------------------------" << endl;
    }
}

//untuk menampilkan semua transaksi
void display_transaksi(){
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0 ; i < jumlah_transaksi ; i++)
    {
    int p=i+1;
    cout << "nomor pembelian  : " << p << endl;
    cout << "Nama pembeli     : " << transaksi[i].namapembeli << endl;
    cout << "nama barang      : " << transaksi[i].namabarang << endl;
    cout << "harga barang     : " << transaksi[i].hargasatuan << endl;
    cout << "jumlah beli      : " << transaksi[i].jumlahbeli << endl;
    cout << "total harga      : " << transaksi[i].hargatotal << endl;
    cout << "total bayar      : " << transaksi[i].jumlahbayar << endl;
    cout << "kembalian        : " << transaksi[i].kembalian << endl;
    cout << "-------------------------------------------------------------" << endl;
    }
}

//ada eror cuma bisa baca data ke 1 selainnya gada(dah fix)
//untuk menampilkan transaksi user
void display_transaksi_akun(){
    //system("cls");
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0 ; i < jumlah_transaksi ; i++)
    {
        if (username == transaksi[i].namapembeli)
        {
            int p=i+1;
            cout << "nomor pembelian  : " << p << endl;
            cout << "Nama pembeli     : " << transaksi[i].namapembeli << endl;
            cout << "nama barang      : " << transaksi[i].namabarang << endl;
            cout << "harga barang     : " << transaksi[i].hargasatuan << endl;
            cout << "jumlah beli      : " << transaksi[i].jumlahbeli << endl;
            cout << "total harga      : " << transaksi[i].hargatotal << endl;
            cout << "total bayar      : " << transaksi[i].jumlahbayar << endl;
            cout << "kembalian        : " << transaksi[i].kembalian << endl;
            cout << "-------------------------------------------------------------" << endl;
        }   
    }
}

////untuk menampilkan struk pembelian user
void display_struk(){
    int p = jumlah_transaksi;
    cout << "-------------------------------------------------------------" << endl;
    cout << "nomor pembelian  : " << p << endl;
    cout << "Nama pembeli     : " << transaksi[p].namapembeli << endl;
    cout << "nama barang      : " << transaksi[p].namabarang << endl;
    cout << "harga barang     : " << transaksi[p].hargasatuan << endl;
    cout << "jumlah beli      : " << transaksi[p].jumlahbeli << endl;
    cout << "total harga      : " << transaksi[p].hargatotal << endl;
    cout << "total bayar      : " << transaksi[p].jumlahbayar << endl;
    cout << "kembalian        : " << transaksi[p].kembalian << endl;
    cout << "-------------------------------------------------------------" << endl;

}

void capitalize(string& str) {
    // Konversi karakter pertama menjadi huruf besar
    bool capitalize_next = true;
    for (int i = 0; i < str.length(); i++) {
        if (isalpha(str[i])) {
            if (capitalize_next) {
                str[i] = toupper(str[i]);
                capitalize_next = false;
            }
            else {
                str[i] = tolower(str[i]);
            }
        }
        else {
            capitalize_next = true;
        }
    }
}

void linear_search()
{
    string cari;
    cout << "Masukkan nama barang : "; fflush(stdin); getline(cin, cari);
    capitalize(cari);
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < jumlah_barang; i++)
    {
        if (data_barang[i].nama_barang.find(cari) != string::npos)
        {
            cout << "Nama Barang       : " << data_barang[i].nama_barang << endl;
            cout << "Jenis Barang      : " << data_barang[i].jenis_barang << endl;
            cout << "Harga             : " << data_barang[i].detail_barangnya.harga << endl;
            cout << "Jumlah            : " << data_barang[i].detail_barangnya.jumlah << endl;
            cout << "Satuan            : " << data_barang[i].satuan << endl;
            cout << "-------------------------------------------------------------" << endl;
        }
    }
}

void merge(barang arr[], int l, int m, int r, int urut) {
    int n1 = m - l + 1;
    int n2 = r - m;

    barang L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (urut == 1)
        {
        //eror di tanda >= kalau di ganti <=
        if (L[i].nama_barang >= R[j].nama_barang) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        }else{
        if (L[i].jenis_barang >= R[j].jenis_barang) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        }
        
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(barang arr[], int l, int r, int urut) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, urut);
        mergeSort(arr, m + 1, r, urut);

        merge(arr, l, m, r, urut);
    }
}

//untuk registrasi akun
void registrasi_akun(){
    ofstream file;
    file.open("dataakun.csv", ios::out | ios::app);
    bool username_taken = false;
    do {
    	cout << "Masukkan Username : "; fflush(stdin); getline(cin, akun[jumlah_akun].nama);
    	for (int i = 0; i<jumlah_akun; i++){
	    	if (akun[jumlah_akun].nama == "admin" || akun[i].nama == akun[jumlah_akun].nama ){
	    		cout << "============== Maaf Username telah dipakai, silahkan gunakan username lain ============="<< endl;
	    		username_taken = true;
	    		break;
			}
			else {
				username_taken = false;
			}
		}
	}while(username_taken);
	
	file << akun[jumlah_akun].nama << ",";
	cout << "Masukkan Password : "; fflush(stdin); getline(cin, akun[jumlah_akun].kode);
 	file << akun[jumlah_akun].kode << "\n";
	cout << "============= Akun berhasil di buat =============" << endl;
	file.close();
	jumlah_akun++;
	}	 
 
bool isValidInput(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}  

//untuk menambahkan barang

void tambah_barang(){
    string stok;
    //system("cls");
    cout << " =======================================" << endl;
    cout << " =           TAMBAH BARANG             =" << endl;
    cout << " =======================================" << endl;
	barang barang_baru;
    ofstream file;
    file.open("databarang.csv", ios::out | ios::app);
    cout << "Masukkan Nama barang   : "; fflush(stdin); getline(cin, data_barang[jumlah_barang].nama_barang);
    capitalize(data_barang[jumlah_barang].nama_barang);
    // Cek apakah barang sudah ada dalam daftar
      bool ditemukan = false;
      for (int i = 0; i < jumlah_barang; i++) {
        if (data_barang[i].nama_barang  == data_barang[jumlah_barang].nama_barang) {
          // Jika sudah ada, input stok saja
          while (true)
          {
            cout << "Masukkan Stok Barang  : " ; cin >> stok;
			if (isValidInput(stok)) {
	            data_barang[jumlah_barang].detail_barangnya.jumlah += stoi(stok);
	            break;
            }
            else {
	            cout << "Input tidak valid. Masukkan bilangan bulat." << endl;
	        }
	    }
	    file << data_barang[jumlah_barang].detail_barangnya.jumlah << "\n";
        ditemukan = true;
        break;
        }
      }

      if (!ditemukan) {
        // Jika belum ada, input stok dan harga
		file << data_barang[jumlah_barang].nama_barang << ",";
		while(true){
			cout << "Masukkan Jenis barang [Material/Alat]  : "; fflush(stdin); getline(cin, data_barang[jumlah_barang].jenis_barang);
	    	capitalize(data_barang[jumlah_barang].jenis_barang);
	    	if (data_barang[jumlah_barang].jenis_barang == "Material" || data_barang[jumlah_barang].jenis_barang == "Alat"){
	    		file << data_barang[jumlah_barang].jenis_barang << ",";	
	    		break;
			}
			else{
				cout << "Jenis tidak dikenali" << endl;
				continue;
			}
		}
		
		while(true){
            string harga;
            cout << "Masukkan Harga Barang   :" ; cin >> harga;
			if (isValidInput(harga)) {
	            data_barang[jumlah_barang].detail_barangnya.harga = stoi(harga);
	            break;
        	}
	        else {
	            cout << "Input tidak valid. Masukkan bilangan bulat." << endl;
	        }
	    }
        file << data_barang[jumlah_barang].detail_barangnya.harga << ",";

	    while(true){
			cout << "Masukkan Jenis satuan barang [Sak/Pcs]  : "; fflush(stdin); getline(cin, data_barang[jumlah_barang].satuan);
	    	capitalize(data_barang[jumlah_barang].satuan);
	    	if (data_barang[jumlah_barang].satuan == "Sak" || data_barang[jumlah_barang].satuan == "Pcs"){
	    		file << data_barang[jumlah_barang].satuan << ",";	
	    		break;
			}
			else{
				cout << "Jenis tidak dikenali" << endl;
				continue;
			}
		}
        while(true){
            string stok;
            cout << "Masukkan Stok Barang   :" ; cin >> stok;
			if (isValidInput(stok)) {
	            data_barang[jumlah_barang].detail_barangnya.jumlah = stoi(stok);
	            break;
        	}
	        else {
	            cout << "Input tidak valid. Masukkan bilangan bulat." << endl;
	        }
	    }
	    file << data_barang[jumlah_barang].detail_barangnya.jumlah << "\n";

	    cout << "============ Barang berhasil di tambahkan ============" << endl;
	    file.close();
	    jumlah_barang++;
      }
    
}

//untuk mengubah barang
void ubah_barang(){
    int ganti;
    int harga_update;
    int jumlah_update;
    //system("cls");
    cout << " =======================================" << endl;
    cout << " ¦             UBAH BARANG             ¦" << endl;
    cout << " =======================================" << endl;
    display_barang();
    cout << "Masukkan nomor data yang akan diubah = "; cin >> pilih;
    if (menu_valid(pilih)) {
	        ganti = stoi(pilih);
        if (ganti > 0 && ganti <= jumlah_barang)
        {
            cout << "Masukkan Nama barang   : "; fflush(stdin); getline(cin, data_barang[ganti - 1].nama_barang);
            cout << "Masukkan jenis barang  : "; fflush(stdin); getline(cin, data_barang[ganti - 1].jenis_barang);
            while(true){
                string harga;
                cout << "Masukkan Harga Barang   :" ; cin >> harga;
                if (isValidInput(harga)) {
                    harga_update = stoi(harga);
                    break;
                }
                else {
                    cout << "Input tidak valid. Masukkan bilangan bulat." << endl;
                }
            }
            string jen;
            while(true){
			    cout << "Masukkan Jenis satuan barang [Sak/Pcs]  : "; fflush(stdin); getline(cin, jen);
	    	    capitalize(jen);
                if (jen == "Sak" || jen == "Pcs"){
                    data_barang[jumlah_barang].satuan = jen;	
                    break;
                }
                else{
                    cout << "Jenis tidak dikenali" << endl;
                    continue;
                }
		    }
            data_barang[ganti - 1].detail_barangnya.harga = harga_update;
            while(true){
                string stok;
                cout << "Masukkan Stok Barang  :" ; cin >> stok;
                if (isValidInput(stok)) {
                    jumlah_update = stoi(stok);
                    break;
                }
                else {
                    cout << "Input tidak valid. Masukkan bilangan bulat." << endl;
                }
            }
            data_barang[ganti - 1].detail_barangnya.jumlah = jumlah_update;
            cout << "============== Barang berhasil di ubah ==============" << endl;
            repl_barang();
        }
        else
        {
            cout << "============== nomor barang tidak ada ==============" << endl;
        }
    }
     else
        {
            cout << "============== nomor barang tidak ada ==============" << endl;
        }
}
//masih ada salh hapus ketika hapus barang terakhir malah terhapus barng pertama(dah fix)
//untuk hapus barang
void menu_urutbarang(){
    while (menu != 8){
        cout << " =======================================" << endl;
        cout << " =           URUTKAN BARANG            =" << endl;
        cout << " =======================================" << endl;
        cout << " =======================================" << endl;
        cout << " =       1. BERDASARKAN JENIS          =" << endl;
        cout << " =       2. BERDASARKAN NAMA           =" << endl;
        cout << " =       8. KEMBALI                    =" << endl;
        cout << " =======================================" << endl;
        cout << " Pilih : " ; cin >> pilih;
        //system("cls");
        if (menu_valid(pilih)) {
            menu = stoi(pilih);
            switch(menu){
                case 1 :
                    mergeSort(data_barang, 0, n - 1, 2);
                    cout << "\n============ Setelah diurutkan berdasarkan jenis: ============\n";
                    display_barang();
                    menu = 8;
                    break;
                case 2:
                    mergeSort(data_barang, 0, n - 1, 1);
                    cout << "\n============ Setelah diurutkan berdasarkan nama: ============\n";
                    display_barang();
                    menu = 8;
                    break;
                case 8:
                    break;
                default:
                    cout << "============ Pilihan Tidak Tersedia ============" << endl;
                    break;
            }
        }
        else {
            cout << "============ Masukkan Angka !!! ============" << endl;
        }
    }
}

void hapus_barang(){
    while(true){
        int hapus;
        //system("cls");
        cout << " =======================================" << endl;
        cout << "             HAPUS BARANG             =" << endl;
        cout << " =======================================" << endl;
        display_barang();
        cout << "Masukkan Nomor Barang yang Ingin Dihapus " ; cin >> pilih;
        if (menu_valid(pilih)) {
            hapus = stoi(pilih);
            if (hapus > 0 && hapus <= jumlah_barang){
                for (int i = hapus-1; i < jumlah_barang; i++){
                    data_barang[i] = data_barang[i+1];
                }
                jumlah_barang -= 1;
                cout << "============= Barang berhasil di hapus =============" << endl;
                repl_barang();  
                break;      
            }
            else{
                cout << "============= Nomor Barang Tidak Ada =============" << endl;
            }
        }
        else {
            cout << "------------ Masukkan Angka !!! ------------" << endl;
        }
        break;
    }
}


//untuk beli barang
void beli_barang(){
    //masih error ketika jumlah, barang, bayar tidak sesuai dan belum mengurangi stock barang(dah fix)
    //belum bisa membatalkan transaksi(dah fix)
    //system("cls");
    cout << " =======================================" << endl;
    cout << " =              MENU BELI              =" << endl;
    cout << " =======================================" << endl;
    display_barang();
    string konfirmasi;
    int nomorbeli;
    int jumlahbeli;
    int totalharga;
    int hargabarang;
    int totalbayar;
    int kembalian;
    cout << "masukkan nomor barang yang akan di beli  :"; cin >> pilih;
    if (menu_valid(pilih)) {
        nomorbeli = stoi(pilih);
        while (true){
            if (nomorbeli <= jumlah_barang && data_barang[nomorbeli].detail_barangnya.jumlah == 0)
            {
                ofstream file;
                file.open("datatransaksi.csv", ios::out | ios::app);
                nomorbeli = nomorbeli-1;
                hargabarang = data_barang[nomorbeli].detail_barangnya.harga;
                jumlahbeli = val_int("masukkan jumlah barang yang akan di beli : ");

                while (jumlahbeli > data_barang[nomorbeli].detail_barangnya.jumlah){
                    jumlahbeli = val_int("barang tidak cukup masukkan jumlah barang yang akan di beli : ");
                }
                
                totalharga = jumlahbeli * data_barang[nomorbeli].detail_barangnya.harga;

                cout << "============ detail pesanan ============" << endl;
                cout << "pembeli            :" << username << endl;
                cout << "barang yg dibeli   :" << data_barang[nomorbeli].nama_barang << endl;
                cout << "harga barang       :" << hargabarang << endl;
                cout << "total beli         :" << jumlahbeli << endl;
                cout << "total harga        :" << totalharga << endl;

                totalbayar = val_int("masukkan bayaran anda : ");

                while (totalbayar < totalharga)
                {
                    totalbayar = val_int("bayaran kurang masukkan bayaran anda : ");
                }
                kembalian = totalbayar - totalharga;

                cout << "berrhasil" << endl;
                cout << "total bayar       :" << totalbayar << endl;
                cout << "total kembalian   :" << kembalian << endl;
                cout << "========================================" << endl;

                transaksi[jumlah_transaksi].namapembeli = username ;
                transaksi[jumlah_transaksi].namabarang = data_barang[nomorbeli].nama_barang;
                transaksi[jumlah_transaksi].hargasatuan = hargabarang;
                transaksi[jumlah_transaksi].jumlahbeli = jumlahbeli;
                transaksi[jumlah_transaksi].hargatotal = totalharga;
                transaksi[jumlah_transaksi].jumlahbayar = totalbayar;
                transaksi[jumlah_transaksi].kembalian = kembalian;
                display_struk();

                konfirmasi = val_yatdk("pesanan benar[y/n] : ");
                if (konfirmasi == "y")
                {
                    data_barang[nomorbeli].detail_barangnya.jumlah = data_barang[nomorbeli].detail_barangnya.jumlah - jumlahbeli;
                    file << username << ",";
                    file << data_barang[nomorbeli].nama_barang << ",";
                    file << hargabarang << ",";
                    file << jumlahbeli << ",";
                    file << totalharga << ",";
                    file << totalbayar << ",";
                    file << kembalian << "\n";
                    cout << "============== Transaksi Berhasil ==============" << endl;
                    jumlah_transaksi++;
                    repl_barang();
                    read_file_transaksi();
                }
                else{
                    cout << "============== pesanan di batalkan ==============" << endl;
                }
                file.close();
                break;
            }
            else
            {
                cout << "============== barang tidak ada ==============" << endl;
                break;
            }
        }
    }
    else {
        cout << "============== Masukkan Angka !!! ==============" << endl;
    } 
}


//untuk menampilkan menu admin
void menu_admin(){
    while (menu != 9){
        cout << " =======================================" << endl;
        cout << " =              MENU ADMIN             =" << endl;
        cout << " =======================================" << endl;
        cout << " =======================================" << endl;
        cout << " =           1.  LIHAT BARANG          =" << endl;
        cout << " =           2.  TAMBAH BARANG         =" << endl;
        cout << " =           3.  UBAH BARANG           =" << endl;
        cout << " =           4.  HAPUS BARANG          =" << endl;
        cout << " =           5.  RIWAYAT TRANSAKSI     =" << endl;
        cout << " =           6.  CARI BARANG           =" << endl;
        cout << " =           9.  EXIT                  =" << endl;
        cout << " =======================================" << endl;
        cout << " Pilih : " ; cin >> pilih;
        //system("cls");
       if (menu_valid(pilih)) {
	            menu = stoi(pilih);
                switch(menu){
				case 1:
					menu_urutbarang();
					break;
				case 2:
					tambah_barang();
					break;
				case 3:
					ubah_barang();
					break;
				case 4:
					hapus_barang();
					break;
				case 5:
					display_transaksi();
					break;
				case 6:
                    linear_search();
					break;
				case 9:
					break;
				default:
					 cout << "============ Pilihan Tidak Tersedia ============" << endl; 
			}
    	}

        else {
	           cout << "============ Masukkan Angka !!! ============" << endl;
	    }
	}
}

//untuk menampilkan menu user
void menu_user(){
    while (menu != 9){
        cout << " =======================================" << endl;
        cout << " =           MENU USER                 =" << endl;
        cout << " =======================================" << endl;
        cout << " =======================================" << endl;
        cout << " =       1.  LIHAT BARANG              =" << endl;
        cout << " =       2.  BELI BARANG               =" << endl;
        cout << " =       3.  LIHAT TRANSAKSI USER      =" << endl;
        cout << " =       4.  CARI BARANG               =" << endl;
        cout << " =       9.  EXIT                      =" << endl;
        cout << " =======================================" << endl;
        cout << "Pilih : " ; cin >> pilih;
        //system("cls");
        if (menu_valid(pilih)) {
	            menu = stoi(pilih);
                switch(menu){
		    	case 1:
                    menu_urutbarang();
		        	break;
		    	case 2:
		    		beli_barang();
		    		break;
		    	case 3:
		    		display_transaksi_akun();
		    		break;
		    	case 4:
		    		linear_search();
		    		break;
		    	case 9:
		    		break;
		    	default :
		    		cout << "============= Pilihan Tidak Tersedia =============" << endl;
			}
    	}
        else {
	           cout << "============= Pilihan Tidak Tersedia =============" << endl;
	    }
    }
}

//untuk verifikasi login user
void login(){
	string password;
    //system("cls");
    cout << " =======================================" << endl;
    cout << " =                LOGIN                =" << endl;
    cout << " =======================================" << endl;
	cout << " Masukkan Username : "; fflush(stdin); getline(cin, username);
    cout << " Masukkan Password : "; fflush(stdin); getline(cin, password);
    if (username == "admin" && password == "admin123"){
    	cout << "========= Login Berhasil =========" << endl;
    	menu_admin();
	}
    else {
    	for (int i = 0; i < jumlah_akun; i++){
	        if (username == akun[i].nama && password == akun[i].kode){
	            cout << "========= Login Berhasil =========" <<endl;
	            menu_user();
	        }           	        	
	    }
	cout << "========= Username atau Password yang anda masukkan salah!!! =========" << endl;
	}
}
 
//tampilan awal
int main(){
    read_file_akun();
    read_file_barang();
    read_file_transaksi();
    while (true){
        cout << " ====================================" << endl;
        cout << " = PROGRAM TOKO BANGUNAN JAYA ABADI -" << endl;
        cout << " =====================================" << endl;
        cout << " ====================================" << endl;
        cout << " =            1.  LOGIN             =" << endl;
        cout << " =            2.  Register          =" << endl;
        cout << " =            9.  EXIT              =" << endl;
        cout << " ====================================" << endl;
        cout << "Pilih : " ; cin >> pilih;
        //system("cls");
        if (menu_valid(pilih)) {
	            menu = stoi(pilih);
                switch(menu){
	        	case 1:
	        		login();
	        		break;
	        	case 2:
	        		registrasi_akun();
	        		break;
	        	case 9 :
                cout << " ==============================================" << endl;
                cout << " = TERIMAKASIH TELAH MENGGUNAKAN PROGRAM KAMI =" << endl;
                cout << " =               DIBUAT OLEH                  =" << endl;
                cout << " ="<< *ptr1 <<                               "=" << endl;
                cout << " ="<< *ptr2 <<                               "=" << endl;
                cout << " ="<< *ptr3 <<                               "=" << endl;
                cout << " ="<< *ptr4 <<                               "=" << endl;
                cout << " ==============================================" << endl;
	        		return 0;
	        	default :
	        		cout << "========= Pilihan Tidak Tersedia =========" << endl;			
			}
		}
        else {
	            cout << "========= Pilihan Tidak Tersedia =========" << endl;
	    }
    }
}


// admin --> laporan pembelian, searching, sorting, (hapus menu liat akun pembeli), crud barang, login
// user  --> beli barang, lihat barang, searching, sorting, laporan pembelian(akun sendiri), regis dan login, tampilkan struk pembelian


//pembagian tugas jua di tanya
// konsul 2 --> pas beli(bagian int) input minus atau koma masih eror, pas tambah brg kalau barang dah ada buat ga dobel jadi dia tambah jumlah
// --> login jadikan 1, pas regis kalau nama user dah ada harus di ganti, pas selesai pesan atau batal tanya mau beli lagi atau ga
// --> tambahkan kode barang, 


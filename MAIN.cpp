#include<stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>                                                                                                                                  
#include <conio.h>
#include <string.h>
#include <math.h>
#include<time.h>
#include <unistd.h>


bool chooseMode();
int chooseLevel();
void startGame();
int viewHelp();
int viewAbout();
int viewHighScore();
int exit();
void printBoard();
void entryName();
int	turnP1();
int	turnP2();
void highScore();
void assign1_LetterBlock();
void assign1_Rack();
void assign1_Board();
void assign1_array_temp();
bool isLetterAvailableP1();
bool isLetterAvailableP2();
void randomizeRackP1();
void randomizeRackP2();
int isEndGame();
int turn();
void entryLetter();
int check();
int checkIndex(); //check apakah index yang dientrykan tidak akan menimpa huruf yang sudah ada di board
bool checkAround(bool spaceIsWord);//check apakah di atas, bawah, kiri, atau kanan ada huruf atau tidak (huruf yang dientry harus bersambung dengan sebuah huruf lagi)
void checkNoSpace(bool *line, bool *spaceIsWord); //check apakah yang dientrykan ada ruang kosong atau tidak
int checkRack(); //check apakah yang dientrykan ada di rack atau tidak
int checkLine(); //check apakah yang dientrykan segaris atau tidak
bool checkWord(); //check apakah yang dientrykan ada pada kamus atau tidak
int entryLetter_first();
void entryLetter_second();
void entryLetter_continue(char *stillEntry);
void pullback();
int minBoard();
int maxBoard();
//bool toDictionary(temp array_check[]);		akan ditulis ulang setelah pembuatan tipe data bentukan temp
//bool checkFormedWords(temp array_check[]);		akan ditulis ulang setelah pembuatan tipe data bentukan temp
//void scoring(temp array_check[], int b);        akan ditulis ulang setelah pembuatan tipe data bentukan temp
//void bonusLetter(int *point, temp array_check[],  int a);	akan ditulis ulang setelah pembuatan tipe data bentukan temp
//void bonusWord(int *scor_temp, temp array_check[], int a); akan ditulis ulang setelah pembuatan tipe data bentukan temp


typedef struct {
   	char letter;		//hurufnya
   	int totalLetter;	//jumlahnya
   	int point;			//poinnya
} letterBlock;


typedef struct{
    char name [10];
	int turn_noPoint;		//jumlah giliran berturut turut yang tak menghasilkan poin
   	int skor;				//skor pemain
   	int level_choosed;  	//level yang dipilih
	letterBlock A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;	
   	int totalTurn;			//jumlah giliran yang telah dimainkan pemain
   	bool vsComp;			//apakah melawan komputer? (jika true, berarti melawan komputer, jika fales, maka melawan player
	bool is_comp;			
	bool isTurn; 			//apakah gilirannya?
} player;
player p1, p2;

typedef struct{   		//penampung sementara sebelum huruf yang dientry masuk ke board;
	int kolom;
	int baris;
	char huruf;	
} temp;
temp array_temp[7], arrFormedWords[100][2];		//arrFormedWords dibuat 2 kolom. 1 kolom untuk menampung index awal dan kolom satunya lagi untuk menampung index akhir sebuah kata yang terbentuk
int formedWords = 0;

bool toDictionary(temp array_check[]);	
bool checkFormedWords(temp array_check[], int b);	
void scoring(temp array_check[], int b); 
void bonusLetter(int *point, temp array_check[], int a);
void bonusWord(int *scor_temp, temp array_check[], int a);

//inisialisasi awal array_temp
void assign1_array_temp(){
	int i;
	for (i = 0; i<7; i++){
		array_temp[i].baris = 20;	//20 agar diluar index board
		array_temp[i].kolom = 20;	//20 agar diluar index board
		array_temp[i].huruf = '_';
	}
}
bool segaris_baris = false; //jika segaris berdasarkan baris, maka akan bernilai true
bool segaris_kolom = false; //jika segaris berdasarkan kolom, maka akan bernilai true
int i = 0; //iterasi

//inisialisasi letterBlock
void assign1_LetterBlock(){
	p1.A.letter = 'A';		p1.A.totalLetter = 9;		p1.A.point = 1;
	p1.B.letter = 'B';		p1.B.totalLetter = 2;		p1.B.point = 3;
	p1.C.letter = 'C';		p1.C.totalLetter = 2;		p1.C.point = 3;
	p1.D.letter = 'D';		p1.D.totalLetter = 4;		p1.D.point = 2;
	p1.E.letter = 'E';		p1.E.totalLetter = 12;		p1.E.point = 1;
	p1.F.letter = 'F';		p1.F.totalLetter = 2;		p1.F.point = 4;
	p1.G.letter = 'G';		p1.G.totalLetter = 3;		p1.G.point = 2;
	p1.H.letter = 'H';		p1.H.totalLetter = 2;		p1.H.point = 4;
	p1.I.letter = 'I';		p1.I.totalLetter = 9;		p1.I.point = 1;
	p1.J.letter = 'J';		p1.J.totalLetter = 1;		p1.J.point = 8;
	p1.K.letter = 'K';		p1.K.totalLetter = 1;		p1.K.point = 5;
	p1.L.letter = 'L';		p1.L.totalLetter = 4;		p1.L.point = 1;
	p1.M.letter = 'M';		p1.M.totalLetter = 2;		p1.M.point = 3;
	p1.N.letter = 'N';		p1.N.totalLetter = 6;		p1.N.point = 2;
	p1.O.letter = 'O';		p1.O.totalLetter = 8;		p1.O.point = 1;
	p1.P.letter = 'P';		p1.P.totalLetter = 2;		p1.P.point = 3;
	p1.Q.letter = 'Q';		p1.Q.totalLetter = 1;		p1.Q.point = 10;
	p1.R.letter = 'R';		p1.R.totalLetter = 6;		p1.R.point = 1;
	p1.S.letter = 'S';		p1.S.totalLetter = 4;		p1.S.point = 1;
	p1.T.letter = 'T';		p1.T.totalLetter = 6;		p1.T.point = 1;
	p1.U.letter = 'U';		p1.U.totalLetter = 4;		p1.U.point = 1;
	p1.V.letter = 'V';		p1.V.totalLetter = 2;		p1.V.point = 4;
	p1.W.letter = 'W';		p1.W.totalLetter = 2;		p1.W.point = 4;
	p1.X.letter = 'X';		p1.X.totalLetter = 1;		p1.X.point = 8;
	p1.Y.letter = 'Y';		p1.Y.totalLetter = 2;		p1.Y.point = 4;
	p1.Z.letter = 'Z';		p1.Z.totalLetter = 1;		p1.Z.point = 10;
	
	p2.A.letter = 'A';		p2.A.totalLetter = 9;		p2.A.point = 1;
	p2.B.letter = 'B';		p2.B.totalLetter = 2;		p2.B.point = 3;
	p2.C.letter = 'C';		p2.C.totalLetter = 2;		p2.C.point = 3;
	p2.D.letter = 'D';		p2.D.totalLetter = 4;		p2.D.point = 2;
	p2.E.letter = 'E';		p2.E.totalLetter = 12;		p2.E.point = 1;
	p2.F.letter = 'F';		p2.F.totalLetter = 2;		p2.F.point = 4;
	p2.G.letter = 'G';		p2.G.totalLetter = 3;		p2.G.point = 2;
	p2.H.letter = 'H';		p2.H.totalLetter = 2;		p2.H.point = 4;
	p2.I.letter = 'I';		p2.I.totalLetter = 9;		p2.I.point = 1;
	p2.J.letter = 'J';		p2.J.totalLetter = 1;		p2.J.point = 8;
	p2.K.letter = 'K';		p2.K.totalLetter = 1;		p2.K.point = 5;
	p2.L.letter = 'L';		p2.L.totalLetter = 4;		p2.L.point = 1;
	p2.M.letter = 'M';		p2.M.totalLetter = 2;		p2.M.point = 3;
	p2.N.letter = 'N';		p2.N.totalLetter = 6;		p2.N.point = 2;
	p2.O.letter = 'O';		p2.O.totalLetter = 8;		p2.O.point = 1;
	p2.P.letter = 'P';		p2.P.totalLetter = 2;		p2.P.point = 3;
	p2.Q.letter = 'Q';		p2.Q.totalLetter = 1;		p2.Q.point = 10;
	p2.R.letter = 'R';		p2.R.totalLetter = 6;		p2.R.point = 1;
	p2.S.letter = 'S';		p2.S.totalLetter = 4;		p2.S.point = 1;
	p2.T.letter = 'T';		p2.T.totalLetter = 6;		p2.T.point = 1;
	p2.U.letter = 'U';		p2.U.totalLetter = 4;		p2.U.point = 1;
	p2.V.letter = 'V';		p2.V.totalLetter = 2;		p2.V.point = 4;
	p2.W.letter = 'W';		p2.W.totalLetter = 2;		p2.W.point = 4;
	p2.X.letter = 'X';		p2.X.totalLetter = 1;		p2.X.point = 8;
	p2.Y.letter = 'Y';		p2.Y.totalLetter = 2;		p2.Y.point = 4;
	p2.Z.letter = 'Z';		p2.Z.totalLetter = 1;		p2.Z.point = 10;
}

char rackP1[7], rackP2[7], board[15][15];

//Inisialisasi awal rack
void assign1_Rack(){
	for (i = 0; i<7; i++){
		rackP1[i]='_';
	}
	for (i = 0; i<7; i++){
		rackP2[i]='_';
	}
}
//inisialisasi awal board
void assign1_Board(){
	int x, y;
	for (y = 0; y < 15; y++){
		for (x = 0; x < 15; x++){
			board[y][x]='_';
		}
	}
}






void gotoxy(int x, int y){
                COORD coord;
                coord.X = x;
                coord.Y = y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int main(){
	assign1_LetterBlock();
	assign1_Rack();
	assign1_Board();
	p1.totalTurn = 1;
	p2.totalTurn = 1;
	int menu;
	do{
		printf("Main Menu\n");
		printf("1: Play\n");
		printf("2: Help\n");
		printf("3: About\n");
		printf("4: High Score\n");
		printf("5: Exit\n");
		printf("Pilih Menu: ");
		scanf("%d", &menu);
		printf("=========================================\n");
		switch (menu){
			case 1: chooseMode();
					chooseLevel();	
					entryName();
					startGame();
					if (p1.skor > p2.skor){
						printf("%s memenangkan pertandingan dengan skor %d", p1.name, p1.skor);
					} else {
						printf("%s memenangkan pertandingan dengan skor %d", p2.name, p2.skor);
					}
					
			break;
			case 2: viewHelp();
			break;
			case 3: viewAbout();
			break;
			case 4: viewHighScore();
			break;
			case 5: exit();
			break;
			default: printf("angka yang anda masukkan salah\n");
		}
	} while (menu != 5);	

	
	highScore();
	
	return 0;
}

bool chooseMode(){
	int mode;
	printf("Mode Permainan\n");
	printf("1: Player Vs Player\n");
	printf("2: Player Vs Computer (Fitur Belum Tersedia)\n");
	do {
		printf("Pilih Mode: ");
		scanf("%d", &mode);
		printf("=========================================\n");
		switch (mode){
			case 1: p1.vsComp = false;
			break;
			case 2: p1.vsComp = true; printf("Mohon Maaf, Fitur Belum Tersedia\n");
			break;
			default: printf("angka yang anda masukkan salah\n");
		}
	} while (mode != 1);
	return p1.vsComp;
	
}
int viewHelp(){
	char cukup;
	printf("1. (PENTING) Sebelum memulai permainan, pastikan huruf pada keyboard \n   sudah dalam posisi capslock agar game dapat dimainkan. \n");
	printf("2. Setelah menjalankan program, ketik 1 untuk memulai permainan, lalu tekan enter. \n");
	printf("3. Pilih mode permainan (vs. manusia atau komputer) dan tekan enter untuk memilih. \n");
	printf("4. Pilih level yang diinginkan (easy/medium/hard) lalu tekan enter untuk memilih.\n");
	printf("5. Ketika permainan sudah dimulai, untuk pengentrian huruf pertama ketikkan SATU huruf\n   sesuai yang ada pada rak untuk memasukkan huruf tersebut ke papan sesuai instruksi di bawah papan, lalu tekan enter. \n");
	printf("6. Ketika instruksi 'Apakah anda ingin mengentry huruf lagi' muncul, ketik Y untuk mengentri huruf lagi,\n   atau ketik N jika sudah selesai mengentri huruf. Tekan enter untuk mengonfirmasi pilihan. \n");
	printf("7. Untuk pengentrian huruf kedua, ketikkan dengan format 'nomor kolom{spasi}\n   nomor baris{spasi}huruf', lalu tekan enter. \n");
	printf("8. Untuk pengentrian huruf ketiga dan seterusnya, ketikkan dengan format\n   'nomor kolom/baris{spasi}huruf' lalu tekan enter. \n");
	printf("9. Pada giliran kedua dan seterusnya, cara mengentri huruf pertama sama dengan langkah 7,\n   dan cara mengentri huruf kedua dan seterusnya sama dengan langkah 8.\n");
	printf("10. Ketika instruksi “Apakah anda ingin menarik semua huruf” muncul, ketik Y untuk\n   menghapus semua huruf yang dientrikan pada giliran tersebut, atau ketik N untuk\n   mengakhiri giliran. Tekan enter untuk mengonfirmasi pilihan.\n");
	printf("cukup? (entry huruf apa saja)");
	scanf(" %c", &cukup);
	system("cls");
}
int viewAbout(){
	char cukup;
	printf("About: \n");
	printf("Scrabblizer adalah permainan papan yang dibuat oleh kelompok 4 kelas 1B yang didasarkan pada\npermainan papan bernama Scrabble yang diciptakan pada 1938.\n");
	printf("Scrabblizer dapat dimainkan oleh dua orang pemain untuk bersaing dalam membentuk kata-kata\nke dalam papan permainan seluas 256 persegi.\n");
	printf("Kata-kata tersebut dibentuk dari kumpulan huruf acak yang disusun di atas papan secara\nbertautan sehingga membentuk kata yang sesuai dengan kamus yang berdasar pada Bahasa Inggris.\n");
	printf("Program ini dirilis pada tanggal 10 Januari 2022 untuk memenuhi Tugas Besar Dasar-Dasar Pemrograman.\n");
	printf("\nAuthor:\n");
	printf("Delvito Rahim Derivansyah\n");
	printf("Muhammad Rafi Farhan\n");
	printf("Reihan Hadi Fauzan\n");
	printf("\n");
	printf("Dosen Pengampu:\n");
	printf("Ani Rahmani, S.Si., M.T.\n");
	printf("Lukmanul Hakim Firdaus, S.Kom, M.Kom.\n");
	printf("Asri Maspupah, S.ST., M.T.\n");
	printf("\n");
	printf("2022\n");
	printf("Program Studi D4 Teknik Informatika\n");
	printf("Jurusan Teknik Komputer dan Informatika\n");
	printf("Politeknik Negeri Bandung\n");
	printf("\ncukup? (entry huruf apa saja)");
	scanf(" %c", &cukup);
	system("cls");	
}
int viewHighScore(){
	char cukup;
	printf("Fitur belum tersedia\n");
	printf("cukup? (entry huruf apa saja) ");
	scanf(" %c", &cukup);
	system("cls");	
}
	
int exit(){
}

int chooseLevel(){
	int level;
	printf("Level\n");
	printf("1: Easy\n");
	printf("2: Medium\n");
	printf("3: Hard\n");
	do {
		printf("Pilih Level: ");
		scanf("%d", &level);
		printf("=========================================\n");
		switch (level){
			case 1: p1.level_choosed = 1;
			break;
			case 2: p1.level_choosed = 2;
			break;
			case 3: p1.level_choosed = 3;
			break;
			default: printf("angka yang anda masukkan salah\n"); 		
		}
	} while (level < 1 || level > 3);
	
	return p1.level_choosed;
}

void entryName(){
	system("cls");
	gotoxy(30,10);
	printf("Masukkan nama untuk player 1 (Maks 10 char):\n");
	gotoxy(30,11);
	scanf(" %[^\n]", p1.name);
	gotoxy(30,12);
	printf("Masukkan nama untuk player 2 (Maks 10 char):\n");
	gotoxy(30,13);
	scanf(" %[^\n]", p2.name);
}

void startGame(){
	p1.skor = 0;
	p2.skor = 0;
	
	do {
		p1.isTurn = true;
		p2.isTurn = false;
		turnP1();
		p1.totalTurn++; 
		p1.isTurn = false;
		p2.isTurn = true;
		turnP2();
		p2.totalTurn++;
	} while (isEndGame() == false);
	
}

void printBoard(){
	system("cls");
	gotoxy(23,0); printf("|____*Scrabblizer*____|\n");
	printf("=======================================================================\n");
	
	gotoxy(15,2); printf("_______________SCORE________________");  
	
	gotoxy(15,3); printf("%s", p1.name);
	gotoxy(15,4); printf("%d",p1.skor);
	gotoxy(35,3); printf("%s", p2.name);
	gotoxy(35,4); printf("%d",p2.skor);  

	printf("\n");
	printf("=======================================================================\n"); 
	printf("|Y/X| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| 13| 14|\n");
	printf("|0  |@%c | %c | %c |*%c | %c | %c | %c |@%c | %c | %c | %c |*%c | %c | %c |@%c |\n", board[0][0], board[0][1], board[0][2], board[0][3], board[0][4], board[0][5], board[0][6], board[0][7], board[0][8], board[0][9], board[0][10], board[0][11], board[0][12], board[0][13], board[0][14]);  
	printf("|1  | %c |#%c | %c | %c | %c |$%c | %c | %c | %c |$%c | %c | %c | %c |#%c | %c |\n", board[1][0], board[1][1], board[1][2], board[1][3], board[1][4], board[1][5], board[1][6], board[1][7], board[1][8], board[1][9], board[1][10], board[1][11], board[1][12], board[1][13], board[1][14]);  
	printf("|2  | %c | %c |#%c | %c | %c | %c |*%c | %c |*%c | %c | %c | %c |#%c | %c | %c |\n", board[2][0], board[2][1], board[2][2], board[2][3], board[2][4], board[2][5], board[2][6], board[2][7], board[2][8], board[2][9], board[2][10], board[2][11], board[2][12], board[2][13], board[2][14]);  
	printf("|3  |*%c | %c | %c |#%c | %c | %c | %c |*%c | %c | %c | %c |#%c | %c | %c |*%c |\n", board[3][0], board[3][1], board[3][2], board[3][3], board[3][4], board[3][5], board[3][6], board[3][7], board[3][8], board[3][9], board[3][10], board[3][11], board[3][12], board[3][13], board[3][14]);  
	printf("|4  | %c | %c | %c | %c |#%c | %c | %c | %c | %c | %c |#%c | %c | %c | %c | %c |\n", board[4][0], board[4][1], board[4][2], board[4][3], board[4][4], board[4][5], board[4][6], board[4][7], board[4][8], board[4][9], board[4][10], board[4][11], board[4][12], board[4][13], board[4][14]); 
	printf("|5  | %c |$%c | %c | %c | %c |$%c | %c | %c | %c |$%c | %c | %c | %c |$%c | %c |\n", board[5][0], board[5][1], board[5][2], board[5][3], board[5][4], board[5][5], board[5][6], board[5][7], board[5][8], board[5][9], board[5][10], board[5][11], board[5][12], board[5][13], board[5][14]);  
	printf("|6  | %c | %c |*%c | %c | %c | %c |*%c | %c |*%c | %c | %c | %c |*%c | %c | %c |\n", board[6][0], board[6][1], board[6][2], board[6][3], board[6][4], board[6][5], board[6][6], board[6][7], board[6][8], board[6][9], board[6][10], board[6][11], board[6][12], board[6][13], board[6][14]);  
	printf("|7  |@%c | %c | %c |*%c | %c | %c | %c |!%c!| %c | %c | %c |*%c | %c | %c |@%c |\n", board[7][0], board[7][1], board[7][2], board[7][3], board[7][4], board[7][5], board[7][6], board[7][7], board[7][8], board[7][9], board[7][10], board[7][11], board[7][12], board[7][13], board[7][14]);  
	printf("|8  | %c | %c |*%c | %c | %c | %c |*%c | %c |*%c | %c | %c | %c |*%c | %c | %c |\n", board[8][0], board[8][1], board[8][2], board[8][3], board[8][4], board[8][5], board[8][6], board[8][7], board[8][8], board[8][9], board[8][10], board[8][11], board[8][12], board[8][13], board[8][14]);  
	printf("|9  | %c |$%c | %c | %c | %c |$%c | %c | %c | %c |$%c | %c | %c | %c |$%c | %c |\n", board[9][0], board[9][1], board[9][2], board[9][3], board[9][4], board[9][5], board[9][6], board[9][7], board[9][8], board[9][9], board[9][10], board[9][11], board[9][12], board[9][13], board[9][14]);
	printf("|10 | %c | %c | %c | %c |#%c | %c | %c | %c | %c | %c |#%c | %c | %c | %c | %c |\n", board[10][0], board[10][1], board[10][2], board[10][3], board[10][4], board[10][5], board[10][6], board[10][7], board[10][8], board[10][9], board[10][10], board[10][11], board[10][12], board[10][13], board[10][14]);  
	printf("|11 |*%c | %c | %c |#%c | %c | %c | %c |*%c | %c | %c | %c |#%c | %c | %c |*%c |\n", board[11][0], board[11][1], board[11][2], board[11][3], board[11][4], board[11][5], board[11][6], board[11][7], board[11][8], board[11][9], board[11][10], board[11][11], board[11][12], board[11][13], board[11][14]);  
	printf("|12 | %c | %c |#%c | %c | %c | %c |*%c | %c |*%c | %c | %c | %c |#%c | %c | %c |\n", board[12][0], board[12][1], board[12][2], board[12][3], board[12][4], board[12][5], board[12][6], board[12][7], board[12][8], board[12][9], board[12][10], board[12][11], board[12][12], board[12][13], board[12][14]);  
	printf("|13 | %c |#%c | %c | %c | %c |$%c | %c | %c | %c |$%c | %c | %c | %c |#%c | %c |\n", board[13][0], board[13][1], board[13][2], board[13][3], board[13][4], board[13][5], board[13][6], board[13][7], board[13][8], board[13][9], board[13][10], board[13][11], board[13][12], board[13][13], board[13][14]);  
	printf("|14 |@%c | %c | %c |*%c | %c | %c | %c |@%c | %c | %c | %c |*%c | %c | %c |@%c |\n", board[14][0], board[14][1], board[14][2], board[14][3], board[14][4], board[14][5], board[14][6], board[14][7], board[14][8], board[14][9], board[14][10], board[14][11], board[14][12], board[14][13], board[14][14]);  
	printf("=======================================================================\n");							

	gotoxy(75,1); printf("Letter Points:");
	gotoxy(75,2); printf("1 Point - A, E, I, L, N, O, R, S, T and U");
	gotoxy(75,3); printf("2 Points - D and G");
	gotoxy(75,4); printf("3 Points - B, C, M and P");
 	gotoxy(75,5); printf("4 Points - F, H, V, W and Y");
	gotoxy(75,6); printf("5 Points - K");
	gotoxy(75,7); printf("8 Points - J and X");
	gotoxy(75,8); printf("10 Points - Q and Z");
	gotoxy(75,10); printf("Symbols:");
	gotoxy(75,11); printf("* = letter point x2");
	gotoxy(75,12); printf("$ = letter point x3");
	gotoxy(75,13); printf("# = word point x2");
	gotoxy(75,14); printf("@ = word point x3");
	

	gotoxy(5,23); printf("|________Rack P1_________|");
	gotoxy(9,24); printf(" |%c|%c|%c|%c|%c|%c|%c| ", rackP1[0], rackP1[1], rackP1[2], rackP1[3], rackP1[4], rackP1[5], rackP1[6]);
	gotoxy(43,23); printf("|________Rack P2_________|");
	gotoxy(47,24); printf(" |%c|%c|%c|%c|%c|%c|%c| \n", rackP2[0], rackP2[1], rackP2[2], rackP2[3], rackP2[4], rackP2[5], rackP2[6]);
	printf("=======================================================================\n");
}

void randomizeRackP1(){
	int a;		//a adalah untuk random berapa banyak huruf vokal yang dimasukkan pada looping ini
	int b;		//b dalah angka random untuk huruf rack p1
	bool isi;	//untuk mengetahui apakah suatu index bisa berhasil terisi atau tidak
	
	if (isLetterAvailableP1()){		//apakah P1 masih mempunyai huruf?
		srand(time(0));
		a = rand()%5 + 1;
		for (i=0 ; i<a ; i++) { //pengisian setiap rackP1 untuk huruf vokal
			isi = false;
			if(rackP1[i] == '_'){
				do{
					b = rand()%5 + 1; //mengacak angka untuk dapatkan huruf
					
					switch (b){ 
						case 1: if (p1.A.totalLetter-- > 0) {rackP1[i] = p1.A.letter; isi = true; p1.A.totalLetter--;} 
						break;
						case 2: if (p1.E.totalLetter-- > 0) {rackP1[i] = p1.E.letter; isi = true; p1.E.totalLetter--;} 
						break;
						case 3: if (p1.I.totalLetter-- > 0) {rackP1[i] = p1.I.letter; isi = true; p1.I.totalLetter--;}  
						break;
						case 4: if (p1.O.totalLetter-- > 0) {rackP1[i] = p1.O.letter; isi = true; p1.O.totalLetter--;}
						break;
						case 5: if (p1.U.totalLetter-- > 0) {rackP1[i] = p1.U.letter; isi = true; p1.U.totalLetter--;} 
						break;
					} 
				}	while (isi == false);
			}
		}
		
		for (i ; i<7 ; i++) { //pengisian setiap rackP1 untuk huruf konsonan
			isi = false;
			if(rackP1[i] == '_'){
				do{
					b = rand()%21 + 1; //mengacak angka untuk dapatkan huruf
					switch (b){ 
						case 1: if (p1.B.totalLetter-- > 0) {rackP1[i] = p1.B.letter; isi = true; p1.B.totalLetter--;} 
						break; 
						case 2: if (p1.C.totalLetter-- > 0) {rackP1[i] = p1.C.letter; isi = true; p1.C.totalLetter--;}  
						break;
						case 3: if (p1.D.totalLetter-- > 0) {rackP1[i] = p1.D.letter; isi = true; p1.D.totalLetter--;} 
						break;
						case 4: if (p1.F.totalLetter-- > 0) {rackP1[i] = p1.F.letter; isi = true; p1.F.totalLetter--;} 
						break;
						case 5: if (p1.G.totalLetter-- > 0) {rackP1[i] = p1.G.letter; isi = true; p1.G.totalLetter--;} 
						break;
						case 6: if (p1.H.totalLetter-- > 0) {rackP1[i] = p1.H.letter; isi = true; p1.H.totalLetter--;} 
						break;
						case 7: if (p1.J.totalLetter-- > 0) {rackP1[i] = p1.J.letter; isi = true; p1.J.totalLetter--;} 
						break;
						case 8: if (p1.K.totalLetter-- > 0) {rackP1[i] = p1.K.letter; isi = true; p1.K.totalLetter--;} 
						break;
						case 9: if (p1.L.totalLetter-- > 0) {rackP1[i] = p1.L.letter; isi = true; p1.L.totalLetter--;} 
						break;
						case 10: if (p1.M.totalLetter-- > 0) {rackP1[i] = p1.M.letter; isi = true; p1.M.totalLetter--;} 
						break;
						case 11: if (p1.N.totalLetter-- > 0) {rackP1[i] = p1.N.letter; isi = true; p1.N.totalLetter--;} 
						break;
						case 12: if (p1.P.totalLetter-- > 0) {rackP1[i] = p1.P.letter; isi = true; p1.P.totalLetter--;} 
						break;
						case 13: if (p1.Q.totalLetter-- > 0) {rackP1[i] = p1.Q.letter; isi = true; p1.Q.totalLetter--;}  
						break;
						case 14: if (p1.R.totalLetter-- > 0) {rackP1[i] = p1.R.letter; isi = true; p1.R.totalLetter--;} 
						break;
						case 15: if (p1.S.totalLetter-- > 0) {rackP1[i] = p1.S.letter; isi = true; p1.S.totalLetter--;} 
						break;
						case 16: if (p1.T.totalLetter-- > 0) {rackP1[i] = p1.T.letter; isi = true; p1.T.totalLetter--;} 
						break;
						case 17: if (p1.V.totalLetter-- > 0) {rackP1[i] = p1.V.letter; isi = true; p1.V.totalLetter--;} 
						break;
						case 18: if (p1.W.totalLetter-- > 0) {rackP1[i] = p1.W.letter; isi = true; p1.W.totalLetter--;} 
						break;
						case 19: if (p1.X.totalLetter-- > 0) {rackP1[i] = p1.X.letter; isi = true; p1.X.totalLetter--;} 
						break;
						case 20: if (p1.Y.totalLetter-- > 0) {rackP1[i] = p1.Y.letter; isi = true; p1.Y.totalLetter--;} 
						break;
						case 21: if (p1.Z.totalLetter-- > 0) {rackP1[i] = p1.Z.letter; isi = true; p1.Z.totalLetter--;} 
						break; 
					}
					
				} while (isi == false);
			}
		}
	}
}

void randomizeRackP2(){
	int a;		//a adalah untuk random berapa banyak huruf vokal yang dimasukkan pada looping ini
	int m;		//m dalah angka random untuk huruf rack p2
	bool isi = false;	//untuk mengetahui apakah suatu index bisa berhasil terisi atau tidak
	
	if (isLetterAvailableP2()){
		srand(time(0));
		a = rand()%5 + 1;
		for (i=0 ; i<a ; i++) { //pengisian setiap rackP2 untuk huruf vokal
			isi = false;
			if(rackP2[i] == '_'){
				do{
					m = rand()%5 + 1; //mengacak angka untuk dapatkan huruf
					
					switch (m){ 
						case 1: if (p2.A.totalLetter-- > 0) {rackP2[i] = p2.A.letter; isi = true; p2.A.totalLetter--;} 
						break;
						case 2: if (p2.E.totalLetter-- > 0) {rackP2[i] = p2.E.letter; isi = true; p2.E.totalLetter--;} 
						break;
						case 3: if (p2.I.totalLetter-- > 0) {rackP2[i] = p2.I.letter; isi = true; p2.I.totalLetter--;} 
						break;
						case 4: if (p2.O.totalLetter-- > 0) {rackP2[i] = p2.O.letter; isi = true; p2.O.totalLetter--;}
						break;
						case 5: if (p2.U.totalLetter-- > 0) {rackP2[i] = p2.U.letter; isi = true; p2.U.totalLetter--;} 
						break;
					} 
				}	while (isi == false);
			}
		}
		
		for (i ; i<7 ; i++) { //pengisian setiap rackP2 untuk huruf konsonan
			if(rackP2[i] == '_'){
				do{
					m = rand()%21 + 1; //mengacak angka untuk dapatkan huruf
					switch (m){ 
						case 1: if (p2.B.totalLetter-- > 0) {rackP2[i] = p2.B.letter; isi = true; p2.B.totalLetter--;} 
						break; 
						case 2: if (p2.C.totalLetter-- > 0) {rackP2[i] = p2.C.letter; isi = true; p2.C.totalLetter--;}  
						break;
						case 3: if (p2.D.totalLetter-- > 0) {rackP2[i] = p2.D.letter; isi = true; p2.D.totalLetter--;} 
						break;
						case 4: if (p2.F.totalLetter-- > 0) {rackP2[i] = p2.F.letter; isi = true; p2.F.totalLetter--;} 
						break;
						case 5: if (p2.G.totalLetter-- > 0) {rackP2[i] = p2.G.letter; isi = true; p2.G.totalLetter--;} 
						break;
						case 6: if (p2.H.totalLetter-- > 0) {rackP2[i] = p2.H.letter; isi = true; p2.H.totalLetter--;} 
						break;
						case 7: if (p2.J.totalLetter-- > 0) {rackP2[i] = p2.J.letter; isi = true; p2.J.totalLetter--;} 
						break;
						case 8: if (p2.K.totalLetter-- > 0) {rackP2[i] = p2.K.letter; isi = true; p2.K.totalLetter--;} 
						break;
						case 9: if (p2.L.totalLetter-- > 0) {rackP2[i] = p2.L.letter; isi = true; p2.L.totalLetter--;} 
						break;
						case 10: if (p2.M.totalLetter-- > 0) {rackP2[i] = p2.M.letter; isi = true; p2.M.totalLetter--;} 
						break;
						case 11: if (p2.N.totalLetter-- > 0) {rackP2[i] = p2.N.letter; isi = true; p2.N.totalLetter--;} 
						break;
						case 12: if (p2.P.totalLetter-- > 0) {rackP2[i] = p2.P.letter; isi = true; p2.P.totalLetter--;} 
						break;
						case 13: if (p2.Q.totalLetter-- > 0) {rackP2[i] = p2.Q.letter; isi = true; p2.Q.totalLetter--;}  
						break;
						case 14: if (p2.R.totalLetter-- > 0) {rackP2[i] = p2.R.letter; isi = true; p2.R.totalLetter--;} 
						break;
						case 15: if (p2.S.totalLetter-- > 0) {rackP2[i] = p2.S.letter; isi = true; p2.S.totalLetter--;} 
						break;
						case 16: if (p2.T.totalLetter-- > 0) {rackP2[i] = p2.T.letter; isi = true; p2.T.totalLetter--;} 
						break;
						case 17: if (p2.V.totalLetter-- > 0) {rackP2[i] = p2.V.letter; isi = true; p2.V.totalLetter--;} 
						break;
						case 18: if (p2.W.totalLetter-- > 0) {rackP2[i] = p2.W.letter; isi = true; p2.W.totalLetter--;} 
						break;
						case 19: if (p2.X.totalLetter-- > 0) {rackP2[i] = p2.X.letter; isi = true; p2.X.totalLetter--;} 
						break;
						case 20: if (p2.Y.totalLetter-- > 0) {rackP2[i] = p2.Y.letter; isi = true; p2.Y.totalLetter--;} 
						break;
						case 21: if (p2.Z.totalLetter-- > 0) {rackP2[i] = p2.Z.letter; isi = true; p2.Z.totalLetter--;} 
						break; 
					}
					
				} while (isi == false);
			}
		}
	}
}


bool isLetterAvailableP1(){
	int totalAllLettersP1;
	bool availableP1;

	totalAllLettersP1 = p1.A.totalLetter + p1.B.totalLetter + p1.C.totalLetter + p1.D.totalLetter + p1.E.totalLetter + p1.F.totalLetter + p1.G.totalLetter + p1.H.totalLetter + p1.I.totalLetter + p1.J.totalLetter + p1.K.totalLetter 
	+ p1.L.totalLetter + p1.M.totalLetter + p1.N.totalLetter + p1.O.totalLetter + p1.P.totalLetter + p1.Q.totalLetter + p1.R.totalLetter + p1.S.totalLetter + p1.T.totalLetter + p1.U.totalLetter + p1.V.totalLetter + p1.W.totalLetter + p1.X.totalLetter + p1.Y.totalLetter + p1.Z.totalLetter;
	
	totalAllLettersP1 != 0 ? availableP1 = true : availableP1 = false;   // jika tidak ada huruf tersisa, kondisi false
	
	return availableP1;
}

bool isLetterAvailableP2(){
	int totalAllLettersP2;
	bool availableP2;
	
	totalAllLettersP2 = p2.A.totalLetter + p2.B.totalLetter + p2.C.totalLetter + p2.D.totalLetter + p2.E.totalLetter + p2.F.totalLetter + p2.G.totalLetter + p2.H.totalLetter + p2.I.totalLetter + p2.J.totalLetter + p2.K.totalLetter 
	+ p2.L.totalLetter + p2.M.totalLetter + p2.N.totalLetter + p2.O.totalLetter + p2.P.totalLetter + p2.Q.totalLetter + p2.R.totalLetter + p2.S.totalLetter + p2.T.totalLetter + p2.U.totalLetter + p2.V.totalLetter + p2.W.totalLetter + p2.X.totalLetter + p2.Y.totalLetter + p2.Z.totalLetter;
	
	totalAllLettersP2 != 0 ? availableP2 = true : availableP2 = false;   // jika tidak ada huruf tersisa, kondisi false
	
	return availableP2;
}


int isEndGame(){
	bool endGame = false;
	if (!isLetterAvailableP1() && !isLetterAvailableP2()){
		endGame = true;
	}
	
	return endGame;
}

int TimerGame(){
	
}



void highScore(){
}

int	turnP1(){
	randomizeRackP1();
	printBoard();
	printf("giliran player 1\n");
	turn();
}

int	turnP2(){
	randomizeRackP2();
	printBoard();
	printf("giliran player 2\n");
	turn();
}

int turn(){
	entryLetter();
	
	printBoard();

}

void entryLetter(){
	i = 0; 				//iterasi agar input maksimal 7
	int x = 0;				//sebagai pengganti baris
	int y = 0;				//sebagai pengganti kolom
	bool segaris;  	//mengetahui apakah input ke 2 - 7 segaris dengan input pertama
	bool segaris_kolom, segaris_baris, check_valid;
	char stillEntry;
	int counter = 0;
	char cancel;		//untuk menarik balik semua huruf
	
	do{			//perulangan jika checkAround belum true	
		first:		//untuk fungsi goto
		i = 0;

		assign1_array_temp(); 		//agar data pada turn sebelumnya tidak terbawa;
		
		entryLetter_first();
		
		printf("Apakah anda ingin mengentry huruf lagi (Y/N)? "); // mengetahui apakah akan lanjut entry huruf atau tidak
		scanf(" %c", &stillEntry);
		if (stillEntry != 'N') {
			entryLetter_second();
			entryLetter_continue(&stillEntry);
		}
		
		if (stillEntry == 'N'){
			printf("Apakah anda ingin menarik semua huruf (Y/N)? ");
			scanf(" %c", &cancel);
			if (cancel == 'Y'){
				pullback();
				goto first;
			}
		}
		check_valid = check();
	} while (check_valid == false);
	


	
	
}

int entryLetter_first(){
	i = 0;
	//entry pertama
	int x, y;
	if (p1.totalTurn == 1){  //hanya untuk giliran paling pertama ketika game dimulai
		do{
			do{
				printf("masukkan suatu huruf untuk kotak (7,7):");
				scanf(" %c", &array_temp[i].huruf);
				array_temp[i].kolom = 7;
				array_temp[i].baris = 7;					
			} while (checkRack() == false);
		} while (checkIndex() == false);
	} else {			//selain pada giLiran paling pertama
		do{
			do{
				printf("input ke 1: kolom baris huruf (eg: 7 8 A):");
				scanf(" %d %d %c", &array_temp[i].kolom, &array_temp[i].baris, &array_temp[i].huruf);					
			} while (checkRack() == false);
		} while (checkIndex() == false);		
	}
	
	y = array_temp[i].baris;
	x = array_temp[i].kolom;
	board[y][x] = array_temp[i].huruf;
	printBoard();
	i++;
}

void entryLetter_second(){
	bool segaris = false;
	segaris_baris = false;
	segaris_kolom = false;
	int x, y;

	//entry kedua, sebagai acuan apakah segaris menggunakan kolom atau baris
	do {
		do{
			do {
				printf("input ke 2: kolom baris huruf (eg: 7 8 A):");
				scanf(" %d %d %c", &array_temp[i].kolom, &array_temp[i].baris, &array_temp[i].huruf);
								
			} while (checkIndex() == false);
		} while (checkLine() == false);	
	} while (checkRack() == false);			

	
	//print board
	y = array_temp[i].baris;
	x = array_temp[i].kolom;
	board[y][x] = array_temp[i].huruf;
	printBoard();
	i++;
}

void entryLetter_continue(char *stillEntry){
	//entry ke 3-7
	char still;
	int x, y;
	if (segaris_kolom){
		do{
			printf("Apakah anda ingin mengentry huruf lagi (Y/N)? ");
			scanf(" %c", &still);
			if (still != 'N') {	
				do {
					do{
						printf("input ke-%d: baris huruf (eg: 8 A || kolom sudah terisi oleh %d):", i+1, array_temp[0].kolom);
						scanf(" %d %c", &array_temp[i].baris, &array_temp[i].huruf);
						array_temp[i].kolom = array_temp[0].kolom;							
					} while (checkIndex() == false);
				} while (checkRack() == false);
				y = array_temp[i].baris;
				x = array_temp[i].kolom;
				board[y][x] = array_temp[i].huruf;					
				printBoard();
			}
			i++;
		} while (still != 'N' && i < 7);
	} else {
		do{
			printf("Apakah anda ingin mengentry huruf lagi (Y/N)? ");
			scanf(" %c", &still);
			if (still != 'N') {
				do {
					do{
						printf("input ke-%d: kolom huruf (eg: 8 A || baris sudah terisi oleh %d):", i+1, array_temp[0].baris);
						scanf(" %d %c", &array_temp[i].kolom, &array_temp[i].huruf);
						array_temp[i].baris = array_temp[0].baris;							
					} while (checkIndex() == false);
				} while (checkRack() == false);
				y = array_temp[i].baris;
				x = array_temp[i].kolom;
				board[y][x] = array_temp[i].huruf;
				printBoard();
			}
			i++;
		} while (still != 'N' && i < 7);
	}
	
	*stillEntry = still;
}


int check(){
	bool check = false, noSpace, isAround, isWord, spaceIsWord;
	checkNoSpace(&noSpace, &spaceIsWord);
	if (noSpace == false){
		pullback();
		printf("huruf-huruf yang Anda entry tidak bersambung!\n");
	}
	isAround = checkAround(spaceIsWord);
	if (isAround == false){
		pullback();
		printf("huruf-huruf yang di-entry harus bersambung dengan huruf yang sudah ada di board!\n");
	}	
	isWord = checkWord();
	if (isWord == false){
		pullback();
		printf("Tidak membentuk suatu kata dalam bahasa Inggris!\n");
	}
	
	if (noSpace == true && isAround == true && isWord == true){
		check = true;
	}
	return check;
}

int checkLine(){
	bool segaris;
	if (array_temp[i].kolom == array_temp[0].kolom){
		segaris = true;
		segaris_kolom = true;
	} else if (array_temp[i].baris == array_temp[0].baris){
		segaris = true;
		segaris_baris = true;
	} else {
		segaris = false;
		printf("tidak segaris!\n");
		
	}	
	
	return segaris;
}

void checkNoSpace(bool *line, bool *spaceIsWord){
	int min = minBoard(), max = maxBoard(), x, y;		//min untuk mengetahui index array board yang paling kecil di entry
	int m, counter, a ;		//m, a dan counter adalah sebagai iterasi
	*spaceIsWord=false;
	if (i == 1){
		*line = true;
	
	} else if (segaris_baris){
		*line = false;
		counter = 0;
		m = min;
		do{		//mencari apakah berurutan atau tidak
			*line = false;
			a = 0;
			do {
				if (m+1 == array_temp[a].kolom){
					*line = true;
				} 
				a++;
				
			} while (array_temp[a].kolom < 20 && *line == false);
			
			if(*line == false){	//check apakah di board sudah terisi di koordinat yang kosong ini atau tidak
				y = array_temp[0].baris;
				x = m + 1;
				if (board[y][x] != '_'){  
					*line = true;
					*spaceIsWord = true;
				}
			}
			counter++;
			m++;
		} while (array_temp[counter+1].kolom < 20 && *line == true);//karena jika array_temp tidak diisi apa-apa, dia bernilai awal 20
	
	}else {						//segaris kolom
		*line = false;
		counter = 0;
		m = min;
		do{		//mencari apakah berurutan atau tidak
			*line = false;
			a = 0;
			do {
				if (m+1 == array_temp[a].baris){
					*line = true;
				} 
				a++;
				
			} while (array_temp[a].baris < 20 && *line == false);
			
			if(*line == false){	//check apakah di board sudah terisi di koordinat yang kosong ini atau tidak
				y = array_temp[0].kolom;
				x = m + 1;				
				if (board[x][y] != '_'){  
					*line = true;
					*spaceIsWord = true;
				}
			}
			counter++;
			m++;
		} while (array_temp[counter+1].baris < 20 && *line == true);//karena jika array_temp tidak diisi apa-apa, dia bernilai awal 20
	}
}

int checkIndex(){
	bool available;
	int x = array_temp[i].kolom;
	int y = array_temp[i].baris;
	if (board [y][x] == '_' ){
		available = true;
	} else {
		available = false;
		printf("sudah ada huruf di koordinat tersebut\n");
	}
	
	
	return available;
}

int checkRack(){
	int counter = 0;
	bool available = false;	// untuk P1
	if (p1.isTurn == true){
		do {												//cek apakah huruf yang dientrykan terdapat pada rack
			if (rackP1[counter] == array_temp[i].huruf){
				available = true;
			} else {
				counter++;
			}
		} while (counter < 7 && available == false);
		
		if (available == true){
			rackP1[counter] = '_';
		} else {
			printf("huruf tidak ada di rack\n");
		}
	} else { //untuk p2
		do {												//cek apakah huruf yang dientrykan terdapat pada rack
			if (rackP2[counter] == array_temp[i].huruf){
				available = true;
			} else {
				counter++;
			}
		} while (counter < 7 && available == false);
		
		if (available == true){
			rackP2[counter] = '_';
		} else {
			printf("huruf tidak ada di rack\n");
		}
	}
	
	return available;
}

bool checkAround(bool spaceIsWord){
	int min, max, m, x, y, right, left, up, down;
	bool isAround = false;
	min = minBoard();
	max = maxBoard();
	if (p1.isTurn == true){
		isAround = true;
	} else {
		if (segaris_kolom){
			x = array_temp[0].kolom;
			if (spaceIsWord == true){
				isAround = true;
			} else if (board[min - 1][x] != '_'){
				isAround = true;
			} else if (board[max + 1][x] != '_'){
				isAround = true;
			} else {
				left = x - 1;
				right = x + 1;
				m = min;
				while (m <= max && isAround == false){
					if (board[m][right] != '_' || board[m][left] != '_'){
						isAround = true;
					}
					m++;
				}
			}
		} else {
			y = array_temp[0].baris;
			if (board[y][min - 1] != '_'){
				isAround = true;
			} else if (board[y][max + 1] != '_'){
				isAround = true;
			} else {
				up = y - 1;
				down = y + 1;
				m = min;
				while (m <= max && isAround == false){
					if (board[up][m] != '_' || board[down][m] != '_'){
						isAround = true;
					}
					m++;
				}
			}	
		}
	}
	return isAround;
	
}

bool checkWord(){
	bool isWord = false, isFormedWord = false;
	int a, b, c, d, e, totalWords = 0;
	temp array_check[15];
				
	for (e=0; e < 15; e++){   //agar array kosong
		array_check[e].huruf = 0;
		array_check[e].kolom = 20;	//20 sebagai tanda bahwa di luar board
		array_check[e].baris = 20;	//20 sebagai tanda bahwa di luar board
	}	
	
	for (a = 0; a < 15; a++){			//check horizontal
		for (b = 0; b < 15; b++){
			e = 0;
			while (e < 15 && array_check[e].huruf != 0){   //agar array kosong
				array_check[e].huruf = 0;
				array_check[e].kolom = 20;	//20 sebagai tanda bahwa di luar board
				array_check[e].baris = 20;	//20 sebagai tanda bahwa di luar board
				e++;
			}
			d = 0;
			c = b;
			if (board[a][c] != '_'){
				while (c < 15 && board[a][c] != '_'){
					array_check[d].huruf =  board[a][c];
					array_check[d].baris = a;
					array_check[d].kolom = c;
					d++;
					c++;
				}
				isFormedWord = checkFormedWords(array_check, d);
				if (isFormedWord == false){
					isWord = toDictionary(array_check);
					if (isWord == true){
						totalWords++;
						arrFormedWords[formedWords][0].baris = array_check[0].baris;
						arrFormedWords[formedWords][0].kolom = array_check[0].kolom;
						arrFormedWords[formedWords][1].baris = array_check[d].baris;
						arrFormedWords[formedWords][1].kolom = array_check[d].kolom;
						formedWords++;		
						scoring(array_check , d);
										
					}
					isWord = false;
				}
			}
		}
	}
	
	for (a = 0; a < 15; a++){ 			//check vertikal
		for (b = 0; b < 15; b++){
			e = 0;
			while (e < 15 && array_check[e].huruf != 0){   //agar array kosong
				array_check[e].huruf = 0;
				array_check[e].kolom = 20;	//20 sebagai tanda bahwa di luar board
				array_check[e].baris = 20;	//20 sebagai tanda bahwa di luar board
				e++;
			}
			d = 0;
			c = b;
			
			if (board[c][a] != '_'){
				while (c < 15 && board[c][a] != '_'){
					array_check[d].huruf =  board[c][a];
					array_check[d].kolom = a;
					array_check[d].baris = c;
					d++;
					c++;
				}
				isFormedWord = checkFormedWords(array_check, d);
				if (isFormedWord == false){
					isWord = toDictionary(array_check);
					if (isWord == true){
						totalWords++;
						arrFormedWords[formedWords][0].baris = array_check[0].baris;
						arrFormedWords[formedWords][0].kolom = array_check[0].kolom;
						arrFormedWords[formedWords][1].baris = array_check[d].baris;
						arrFormedWords[formedWords][1].kolom = array_check[d].kolom;
						formedWords++;
						scoring(array_check , d);
					}
					isWord = false;
				}
			}
		}
	}
	if (totalWords != 0){
		isWord = true;
	}
	
	return isWord;
}

bool toDictionary(temp array_check[]){
	bool exist = false;
	int counter;
	char word[30];
	char checkWord[15];
	
	for (counter = 0; counter < 15; counter++){
		checkWord[counter] = tolower(array_check[counter].huruf);
	}
	FILE *dict;
	dict = fopen("Dictionary.txt","r");
	rewind(dict);
	fscanf(dict, "%s\n", &word);
	while(!feof(dict) && exist == false){
		if(strcmp(checkWord,word)==0){
			exist = true;
		}else{
			fscanf(dict, "%s\n", &word);
	 }
	}
	
	fclose(dict);
	
	return exist;
}

	
bool checkFormedWords(temp array_check[], int b){
	int a = 0;		//iteration
	bool isFormedWord = false;
	
	while (a < formedWords && isFormedWord == false){
		if ((arrFormedWords[a][0].baris == array_check[0].baris && arrFormedWords[a][0].kolom == array_check[0].kolom) && (arrFormedWords[a][1].baris == array_check[b].baris && arrFormedWords[a][1].kolom == array_check[b].kolom)){
			isFormedWord = true;
		}
		a++;
	}
	return isFormedWord;
	
}

void scoring(temp array_check[], int b){
	int scor_temp=0, a, point;
	char letter_temp;
	
	for(a = 0; a <= b; a++){
		letter_temp = array_check[a].huruf;
		switch(letter_temp){ 
			 case 'A': point = p1.A.point; break;
			 case 'B': point = p1.B.point; break; 
			 case 'C': point = p1.C.point; break;
			 case 'D': point = p1.D.point; break;
			 case 'E': point = p1.E.point; break;
			 case 'F': point = p1.F.point; break;
			 case 'G': point = p1.G.point; break;
			 case 'H': point = p1.H.point; break;
			 case 'I': point = p1.I.point; break;
			 case 'J': point = p1.J.point; break;
			 case 'K': point = p1.K.point; break;
			 case 'L': point = p1.L.point; break;
			 case 'M': point = p1.M.point; break;
			 case 'N': point = p1.N.point; break;
			 case 'O': point = p1.O.point; break;
			 case 'P': point = p1.P.point; break;
			 case 'Q': point = p1.Q.point; break;
			 case 'R': point = p1.R.point; break;
			 case 'S': point = p1.S.point; break;
			 case 'T': point = p1.T.point; break;
			 case 'U': point = p1.U.point; break;
			 case 'V': point = p1.V.point; break;
			 case 'W': point = p1.W.point; break;
			 case 'X': point = p1.X.point; break;
			 case 'Y': point = p1.Y.point; break;
			 case 'Z': point = p1.Z.point; break; 
		}
		bonusLetter(&point, array_check, a);
		scor_temp += point;
	}
	for(a = 0; a <= b; a++){
		bonusWord(&scor_temp, array_check, a);
	}
	
	
	if (p1.isTurn == true){
		p1.skor += scor_temp;
	} else {
		p2.skor += scor_temp;
	}
}

void bonusLetter(int *point, temp array_check[] , int a) {
	int y,x;
	y = array_check[a].baris;
	x = array_check[a].kolom;
	
	if ( (y == 0 && x == 3) || (y == 3 && x == 0) ||
		 (y == 0 && x == 11) || (y == 11 && x == 0) ||
		 (y == 2 && x == 6) || (y == 6 && x == 2) ||
		 (y == 2 && x == 8) || (y == 8 && x == 2) ||
		 (y == 3 && x == 7) || (y == 7 && x == 3) ||
		 (y == 6 && x == 8) || (y == 8 && x == 6) ||
		 (y == 8 && x == 8) || (y == 6 && x == 6) ||
		 (y == 8 && x == 12) || (y == 12 && x == 8) ||
		 (y == 11 && x == 7) || (y == 7 && x == 11) ||
		 (y == 11 && x == 14) || (y == 14 && x == 11) ||
		 (y == 12 && x == 6) || (y == 6 && x == 12) ||
		 (y == 14 && x == 3) || (y == 3 && x == 14)
	){
		*point *= 2;
	}
	if ( (y == 1 && x == 5) || (y == 5 && x == 1) ||
		 (y == 1 && x == 9) || (y == 9 && x == 1) ||
		 (y == 5 && x == 5) || (y == 9 && x == 9) ||
		 (y == 5 && x == 13) || (y == 13 && x == 5) ||
		 (y == 5 && x == 9) || (y == 9 && x == 5) ||
		 (y == 9 && x == 13) || (y == 13 && x == 9) 
	){
		*point *= 3;
	}
}

void bonusWord(int *scor_temp, temp array_check[], int a){
	int y,x;
	y = array_check[a].baris;
	x = array_check[a].kolom;
	
	if ( (y == 1 && x == 1) || (y == 2 && x == 2) ||
		 (y == 3 && x == 3) || (y == 4 && x == 4) ||
		 (y == 11 && x == 11) || (y == 12 && x == 12) ||
		 (y == 10 && x == 10) || (y == 13 && x == 13) ||
		 (y == 1 && x == 13) || (y == 13 && x == 1) ||
		 (y == 2 && x == 12) || (y == 12 && x == 2) ||
		 (y == 3 && x == 11) || (y == 11 && x == 3) ||
		 (y == 4 && x == 10) || (y == 10 && x == 4) 
	){
		*scor_temp *= 2;
	}
	if ( (y == 0 && x == 0) || (y == 14 && x == 14) ||
		 (y == 0 && x == 14) || (y == 14 && x == 0) ||
		 (y == 7 && x == 14) || (y == 14 && x == 7) ||
		 (y == 0 && x == 7) || (y == 7 && x == 0) 
	){
		*scor_temp *= 3;
	}	
}

void pullback(){
	bool rackRefilled;
	int x, y, counter = 0;
	i = 0;
	if(p1.isTurn == true){			//cek p1
		do{
			rackRefilled = false;
			y = array_temp[i].baris;
			x = array_temp[i].kolom;
			while (rackRefilled == false && counter < 7){
				if (rackP1[counter] == '_'){
					rackP1[counter] = board[y][x];
					board[y][x] = '_';
					printBoard();
					rackRefilled = true;
				}
				counter++;
			}
			i++;
		} while (array_temp[i].baris < 20);			// 20 karena inisialisasi awal dari array temp jika tidak memiliki huruf, maka ia kolomnya bernilai 20
	}


	if(p2.isTurn == true){			//cek p2
		do{
			rackRefilled = false;
			y = array_temp[i].baris;
			x = array_temp[i].kolom;
			while (rackRefilled == false && counter < 7){
				if (rackP2[counter] == '_'){
					rackP2[counter] = board[y][x];
					board[y][x] = '_';
					printBoard();
					rackRefilled = true;
				}
				counter++;
			}
			i++;
		} while (array_temp[i].baris < 20);			// 20 karena inisialisasi awal dari array temp jika tidak memiliki huruf, maka ia kolomnya bernilai 20
	}
}


int minBoard(){
	int counter = 0, min;
	if (segaris_kolom){
		min = array_temp[0].baris;
		do {		//mencari nilai yang paling kecil
			if (array_temp[counter].baris < min){
				min = array_temp[counter].baris;
			}
			counter++;
		} while (array_temp[counter].baris < 20);		//karena jika array_temp tidak diisi apa-apa, dia bernilai awal 20
	} else {
		min = array_temp[0].kolom;
		do {		//mencari nilai yang paling kecil
			if (array_temp[counter].kolom < min){
				min = array_temp[counter].kolom;
			}
			counter++;
		} while (array_temp[counter].kolom < 20);		//karena jika array_temp tidak diisi apa-apa, dia bernilai awal 20
	}
	return min;
}

int maxBoard(){
	int counter = 0, max;
	if (segaris_kolom){
		max = array_temp[0].baris;
		do {		//mencari nilai yang paling kecil
			if (array_temp[counter].baris > max){
				max = array_temp[counter].baris;
			}
			counter++;
		} while (array_temp[counter].baris < 20);		//karena jika array_temp tidak diisi apa-apa, dia bernilai awal 20
	} else {
		max = array_temp[0].kolom;
		do {		//mencari nilai yang paling kecil
			if (array_temp[counter].kolom > max){
				max = array_temp[counter].kolom;
			}
			counter++;
		} while (array_temp[counter].kolom < 20);		//karena jika array_temp tidak diisi apa-apa, dia bernilai awal 20
	}
	return max;
}

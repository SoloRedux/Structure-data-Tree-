#include "headerRoyalTree.h"

// Prosedur initiasi root
// author : Ais Laksana
// I.S : root belum diinisialisasi
// F.S : root sudah diinisialisasi
void init_Root(telm_root *L)
{
    L->root = NULL;
}

// Prosedur untuk membuat semua char pada array of Char menjadi Uppercase
// ref : https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case, GPT
// author : Ais Laksana
// I.S : parameter array of char belum diubah
// F.S : parameter array of char sudah diubah menjadi uppercase
void string_to_uppercase(char *str)
{
    while (*str)
    {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

// keterangan data module

// data info module
// Fungsi meng input data info unknown
// author : Ais Laksana
//
dataInfo ket_unknown()
{
    dataInfo ket;
    strcpy(ket.nama, Unknown_name);
    ket.age = 0;
    ket.gender = Unknown_gender;
    ket.alive = true;
    return ket;
}

// Fungsi meng input data info berdasar parameter
// author : Ais Laksana
// I.S : (dataInfo) belum ada
// F.S : fungsi mereturn (dataInfo) berdasar parameter
dataInfo ket_available(infotype nama[MAX_NAME_LENGTH], int age, char gender)
{
    dataInfo person;
    gender = toupper(gender);
    if (gender != 'L' && gender != 'P')
    {
        gender = Unknown_gender;
    }

    strcpy(person.nama, nama);
    string_to_uppercase(person.nama);
    person.age = age;
    person.gender = gender;
    person.alive = true;
    return person;
}

// Fungsi meng input data info yang diinput user
// author : Ais Laksana
// I.S : (dataInfo) belum ada
// F.S : fungsi mereturn (dataInfo) yang sudah diinput user
dataInfo ket_input()
{
    dataInfo person;
    char gender;
    printf("Masukkan nama : ");
    scanf(" %[^\n]", person.nama);
    string_to_uppercase(person.nama);
    printf("Masukkan umur : ");
    scanf("%d", &person.age);
    do
    {

        int choice;
        printf("Gender : \n1. Laki-laki\n2. Perempuan\n");
        scanf(" %d", &choice);
        if (choice == 1)
        {
            gender = 'L';
        }
        else if (choice == 2)
        {
            gender = 'P';
        }
        gender = toupper(gender);
        if (gender != 'L' && gender != 'P')
        {
            printf("di dunia ini gender hanya ada 2\n");
        }
    } while (gender != 'L' && gender != 'P');

    person.gender = gender;
    person = ket_available(person.nama, person.age, person.gender);
    return person;
}

// Fungsi alokasi node module
// author : Ais Laksana
// I.S : node belum di alokasi
// F.S : fungsi mereturn node yang sudah di alokasi dengan datainfo sesuai dengan parameter
address alok_pointer(dataInfo _info)
{
    address P;
    P = (address)malloc(sizeof(telm_familly));
    if (P != NULL)
    {
        P->info = _info;
    }
    P->node_fs = NULL;
    P->node_mate = NULL;
    P->node_nb = NULL;
    P->node_parrent = NULL;
    return P;
}

// Fungsi alokasi node dengan datainfo unknown
// author : Ais Laksana
// I.S : node belum di alokasi
// F.S : fungsi mereturn node sudah di alokasi dengan (datainfo) unknown
address alok_unknown_pers()
{
    dataInfo person = ket_unknown();
    return alok_pointer(person);
}

// Fungsi alokasi node dengan input parameter
// author : Ais Laksana
// I.S : node belum di alokasi
// F.S : fungsi mereturn node sudah di alokasi berdasar input parameter
address alok_available_pers(infotype name[MAX_NAME_LENGTH], int age, char gender)
{
    dataInfo person = ket_available(name, age, gender);
    return alok_pointer(person);
}

// Fungsi alokasi node dengan input user
// author : Ais Laksana
// I.S : node belum di alokasi
// F.S : fungsi mereturn node sudah di alokasi berdasar input user
address alok_input_pers()
{
    dataInfo person = ket_input();
    return alok_pointer(person);
}

// Prosedur print (dataInfo) module
// author : Ais Laksana
// I.S : dataInfo belum di print
// F.S : dataInfo sudah di print
void print_datainfo(dataInfo X)
{
    infotype status[MAX_NAME_LENGTH];
    printf("Nama : %s\n", X.nama);
    printf("Age : %d\n", X.age);
    printf("Gender : %c\n", X.gender);
    if (X.alive)
    {
        strcpy(status, "Hidup");
    }
    else
    {
        strcpy(status, "Mati");
    }
    printf("Status hidup : %s\n", status);
}

// pointer allocation module

// birth module
// Prosedur memberikan suatu node dengan anak yang tidak diketahui
// author : Ais Laksana
// I.S : (X->node_fs) atau (X->node_fs->node_nb) pada suatu node masih NULL
// F.S : (X->node_fs) atau (X->node_fs->node_nb) menunjuk pada node dengan (ket_unknown()) pada (dataInfo)
void point_birth_unknown(telm_familly *X)
{
    address node = alok_unknown_pers();
    if (X->node_fs == NULL)
    {
        X->node_fs = node;
        if (X->node_mate != NULL)
        {
            X->node_mate->node_fs = node;
        }
    }
    else
    {
        address temp = X->node_fs;
        while (temp->node_nb != NULL)
        {
            temp = temp->node_nb;
        }
        temp->node_nb = node;
    }
    node->node_parrent = X;
}

// Prosedur memberikan suatu node, anak dengan (dataInfo) dari paramerter
// author : Ais Laksana
// I.S : (X->node_fs) atau (X->node_fs->node_nb) pada suatu node masih NULL
// F.S : (X->node_fs) atau (X->node_fs->node_nb) menunjuk pada node dengan (dataInfo) sesuai dengan parameter
void point_birth_available(telm_familly *X, infotype nama[MAX_NAME_LENGTH], int age, char gender)
{
    address node = alok_available_pers(nama, age, gender);
    if (X->node_fs == NULL)
    {
        X->node_fs = node;
        if (X->node_mate != NULL)
        {
            X->node_mate->node_fs = node;
        }
    }
    else
    {
        address temp = X->node_fs;
        while (temp->node_nb != NULL)
        {
            temp = temp->node_nb;
        }
        temp->node_nb = node;
    }
    node->node_parrent = X;
}

// Prosedur memberikan suatu node dengan anak yang diinput user
// author : Ais Laksana
// I.S : (X->node_fs) atau (X->node_fs->node_nb) pada suatu node masih NUL
// F.S : (X->node_fs) atau (X->node_fs->node_nb) menunjuk pada node yang diinput user
void point_birth_input(telm_familly *X)
{
    address node;
    do
    {
        if (X->node_fs != NULL)
        {
            address current = X->node_fs;

            int curr_age = current->info.age;
            while (current->node_nb != NULL && curr_age == 0)
            {
                if (curr_age > current->node_nb->info.age || curr_age == 0)
                {
                    curr_age = current->node_nb->info.age;
                }
                current = current->node_nb;
            }
            node = alok_input_pers();
            if (X->node_fs != NULL && node->info.age > curr_age && curr_age != 0)
            {
                system("cls");
                printf("current age inside restriction %d\n", curr_age);
                printf("Cannot add a brother older than the youngest brother/sister.\n");
                printf("current youngest brother/sister age : %d\n", curr_age);
                node = NULL;
            }
        }
        else if (X->node_fs == NULL)
        {
            node = alok_input_pers();
        }
    } while (node == NULL);

    if (X->node_fs == NULL)
    {
        X->node_fs = node;
        if (X->node_mate != NULL)
        {
            X->node_mate->node_fs = node;
        }
    }
    else
    {
        address temp = X->node_fs;
        while (temp->node_nb != NULL)
        {
            temp = temp->node_nb;
        }
        temp->node_nb = node;
    }
    node->node_parrent = X;
}

// marriage module
// menikahkan node dengan node yang tidak diketahui
// author : Ais Laksana
// I.S : (X->node_mate) pada suatu node masih NULL
// F.S : (X->node_mate) menunjuk pada node dengan (ket_unknown()) pada (dataInfo) dan sebaliknya
void point_marriage_unknown(telm_familly *X)
{
    address node = alok_unknown_pers();
    if (X->node_mate == NULL)
    {
        X->node_mate = node;
        X->node_mate->node_mate = X;
    }
}

// Prosedur menikahkan node dengan node yang pada parameter
// author : Ais Laksana
// I.S : (X->node_mate) pada suatu node masih NULL
// F.S : (X->node_mate) menunjuk pada node (telm_familly Y) dan sebaliknya
void point_marriage_available(telm_familly *X, telm_familly *Y)
{
    if (X->node_mate == NULL)
    {
        X->node_mate = Y;
    }
    else
    {
        printf("%s already married\n", X->info.nama);
    }
    if (Y->node_mate == NULL)
    {
        Y->node_mate = X;
    }
    else
    {
        printf("%s already married\n", Y->info.nama);
    }
}

// Prosedur untuk menikahkan node dengan node yang diinput user
// author : Ais Laksana
// I.S : (X->node_mate) pada suatu node masih NULL
// F.S : (X->node_mate) menunjuk pada node yang diinput user dan sebaliknya
void point_marriage_input(telm_familly *X)
{
    address node = alok_input_pers();
    if (X->node_mate == NULL)
    {
        X->node_mate = node;
    }
    else if (node->node_mate == NULL)
    {
        node->node_mate = X;
    }
    else
    {
        printf("both already married\n");
    }
}

// Prosedur untuk mengubah status hidup node
// author : Ais Laksana
// I.S : status hidup pada (dataInfo) node belum diubah
// F.S : status hidup pada (dataInfo) node belum diubah
void point_kill(telm_familly *X)
{
    X->info.alive = false;
}

// Fungsi yang mereturn nama yang di cari
// author : Daffa Muzhafar & Ais Laksan
// I.S : node belum di cari
// F.S : node yang dicari ditemukan dan di return fungsi
address search(address node, infotype name[MAX_NAME_LENGTH])
{
    if (node == NULL)
    {
        return NULL;
    }

    if (strcmp(node->info.nama, name) == 0)
    {
        return node;
    }
    if (node->node_mate != NULL)
    {
        if (strcmp(node->node_mate->info.nama, name) == 0)
        {
            return node->node_mate;
        }
    }

    address result = search(node->node_fs, name);
    if (result != NULL)
    {
        return result;
    }
    return search(node->node_nb, name);
}

address search_handler(address node, infotype name[MAX_NAME_LENGTH])
{
    char temp_name[MAX_NAME_LENGTH];
    strcpy(temp_name, name);
    string_to_uppercase(temp_name);
    address result = search(node, temp_name);
    if (result == NULL)
    {
        printf("Not found\n");
    }
    else
    {
        printf("Found\n");
    }
    return result;
}

// Prosedur untuk mencetak pohon secara rekursif dengan pre order
// author : Daffa Muzhafar
// I.S : Tree belum tercetak
// F.S : Tree tercetak dengan garis silsilah tiap generasi
void printTree(address root, int level)
{
    if (root == NULL)
        return;
    int i;
    for (i = 0; i < level; i++)
    {

        printf("	|");
    }
    printf("- %s\n", root->info.nama);
    if (root->node_mate != NULL)
    {
        for (i = 0; i < level; i++)
        {

            printf("	|");
        }
        printf("- %s\n", root->node_mate->info.nama);
    }

    printTree(root->node_fs, level + 1);
    printTree(root->node_nb, level);
}

// Prosedur untuk melakukan traversal secara pre-order
// author: Daffa Muzhafar & Ais Laksana
// I.S. : Tree belum
// F.S. : Tree dicetak secara pre-order
void trav_pre_order(address root)
{
    if (root == NULL)
        return;
    printf(" %s", root->info.nama);
    if (root->node_mate != NULL)
    {
        printf(" pasangan dengan %s", root->node_mate->info.nama);
    }
    printf("\n");
    trav_pre_order(root->node_fs);
    trav_pre_order(root->node_nb);
}

// prosedur untuk menulis ulang data pada format string dalam file
// author : Ais Laksana
// I.S : file belum di tulis
// F.S : file sudah di tulis
void serialize_Node(FILE *file, address node, boolean isRoot)
{
    if (node == NULL)
        return;

    if (isRoot)
    {
        fprintf(file, "# Root\n");
    }
    else
    {
        fprintf(file, "# Person\n");
    }

    fprintf(file, "name: %s\n", node->info.nama);
    fprintf(file, "age: %d\n", node->info.age);
    fprintf(file, "gender: %c\n", node->info.gender);
    fprintf(file, "alive: %s\n", node->info.alive ? "true" : "false");
    fprintf(file, "mate: %s\n", node->node_mate ? node->node_mate->info.nama : "null");
    fprintf(file, "first_son: %s\n", node->node_fs ? node->node_fs->info.nama : "null");
    fprintf(file, "next_sibling: %s\n", node->node_nb ? node->node_nb->info.nama : "null");
    fprintf(file, "parent: %s\n", node->node_parrent ? node->node_parrent->info.nama : "null");
    fprintf(file, "\n");

    if (node->node_mate)
    {
        fprintf(file, "# Mate\n");
        fprintf(file, "name: %s\n", node->node_mate->info.nama);
        fprintf(file, "age: %d\n", node->node_mate->info.age);
        fprintf(file, "gender: %c\n", node->node_mate->info.gender);
        fprintf(file, "alive: %s\n", node->node_mate->info.alive ? "true" : "false");
        fprintf(file, "mate: %s\n", node->node_mate->node_mate ? node->node_mate->node_mate->info.nama : "null");
        fprintf(file, "first_son: %s\n", node->node_mate->node_fs ? node->node_mate->node_fs->info.nama : "null");
        fprintf(file, "next_sibling: %s\n", node->node_mate->node_nb ? node->node_mate->node_nb->info.nama : "null");
        fprintf(file, "parent: %s\n", node->node_mate->node_parrent ? node->node_mate->node_parrent->info.nama : "null");
        fprintf(file, "\n");
    }

    serialize_Node(file, node->node_fs, false);
    serialize_Node(file, node->node_nb, false);
}

// Prosedur untuk menghandle serialize node
// author : Ais Laksana
// I.S : file belum disimpan
// F.S : file sudah disimpan
void save_Tree_To_File(const char *filename, telm_root *familyTree)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Unable to open file for writing");
        return;
    }

    serialize_Node(file, familyTree->root, true);

    fclose(file);
}

// prosedur fitur untuk menambah anggota kerajaan
// author : Ais Laksana & Daffa Muzhafar
// I.S : node belum di tambah
// F.S : node sudah di tambah
void tambah_anak(address root)
{
    char name_parent[MAX_NAME_LENGTH];
    address parent;
    do
    {
        system("cls");
        printTree(root, 0);
        printf("Masukkan nama orang tua: ");
        scanf(" %[^\n]", name_parent);
        getchar();
        /* code */
        parent = search_handler(root, name_parent);
        if (parent == NULL)
        {
            system("cls");
            printf("[ %s ] Tidak ditemukan dalam pohon keluarga\n", name_parent);
            printf("\n\tPress any key to continue . . . ");
            getch();
        }
    } while (parent == NULL && strcmp(name_parent, "\n") != 0);

    if (parent == NULL)
    {
        printf("Orang tua tidak ditemukan\n");
        return;
    }
    printf("Data diri calon anak : \n");
    point_birth_input(parent);
    system("cls");
    printTree(root, 0);
    printf("[ %s ] dikaruniai anak\n", parent->info.nama);
    printf("\n\tPress any key to continue . . . ");
    getch();
    system("cls");
}

// prosedur untuk dummy data
void make_tree(telm_root *familyTree)
{
    familyTree->root = alok_available_pers("Root", 50, 'L');
    point_marriage_unknown(familyTree->root);
    point_birth_available(familyTree->root, "Anak1", 10, 'L');
    point_birth_available(familyTree->root, "Anak2", 5, 'P');
    point_birth_available(familyTree->root->node_fs, "Anak1.1", 30, 'L');
    point_birth_available(familyTree->root->node_fs, "Anak1.2", 20, 'L');
    point_birth_available(familyTree->root->node_fs->node_fs, "Anak1.1.1", 10, 'L');
    point_birth_available(familyTree->root->node_fs->node_fs, "Anak1.1.2", 9, 'L');
}

void nikahkan(address root)
{
    if (root == NULL)
    {
        return;
    }
    address temp = NULL;
    do
    {
        system("cls");
        printTree(root, 0);
        printf("Siapa yang ingin dinikahkan : \n");
        char nama[MAX_NAME_LENGTH];
        scanf(" %[^\n]", nama);
        getchar();
        temp = search_handler(root, nama);
        if (temp->node_mate != NULL)
        {
            system("cls");
            printf("[ %s ] Sudah menikah, jangan ganggu yang sudah menikah~\n", temp->info.nama);
            temp = NULL;
            printf("\n\tPress any key to continue . . . ");
            getch();
        }
    } while (temp == NULL);
    printf("Data diri calon pasangan :\n");
    point_marriage_input(temp);
    system("cls");
    printTree(root, 0);
    printf("[ %s ] menikah dengan [ %s ] \n", temp->info.nama, temp->node_mate->info.nama);
    printf("\n\tPress any key to continue . . . ");
    getch();
    system("cls");
}

void tampilkan_informasi(address root)
{
    if (root == NULL)
    {
        return;
    }
    address temp = NULL;
    do
    {
        system("cls");
        printTree(root, 0);
        printf("Siapa yang ingin dilihat informasinya : \n");
        infotype nama[MAX_NAME_LENGTH];
        scanf(" %[^\n]", nama);
        getchar();
        temp = search_handler(root, nama);
        if (temp == NULL)
        {
            system("cls");
            printf("[ %s ] Tidak ditemukan dalam pohon keluarga\n", nama);
            printf("\n\tPress any key to continue . . . ");
            getch();
        }
    } while (temp == NULL);
    system("cls");
    print_datainfo(temp->info);
    printf("\n\tPress any key to continue . . . ");
    getch();
    system("cls");
}

void membunuh(address root)
{
    if (root == NULL)
    {
        return;
    }
    address temp = NULL;
    do
    {
        system("cls");
        printTree(root, 0);
        printf("Siapa aggota yang ingin dibunuh : \n");
        infotype nama[MAX_NAME_LENGTH];
        scanf(" %[^\n]", nama);
        getchar();
        temp = search_handler(root, nama);
        if (temp == NULL)
        {
            system("cls");
            printf("[ %s ] Tidak ditemukan dalam pohon keluarga\n", nama);
            printf("\n\tPress any key to continue . . . ");
            getch();
        }
    } while (temp == NULL);
    system("cls");
    point_kill(temp);
    printf("[ %s ] telah meninggal", temp->info.nama);
    printf("\n\tPress any key to continue . . . ");
    getch();
    system("cls");
}

void penerus(address root){
    if (root == NULL)
    {
        return;
    }
    address temp = NULL;
    do
    {
        system("cls");
        printTree(root, 0);
        printf("Siapa yang ingin dilihat informasinya : \n");
        infotype nama[MAX_NAME_LENGTH];
        scanf(" %[^\n]", nama);
        getchar();
        temp = search_handler(root, nama);
        if (temp == NULL)
        {
            system("cls");
            printf("[ %s ] Tidak ditemukan dalam pohon keluarga\n", nama);
            printf("\n\tPress any key to continue . . . ");
            getch();
        }
    } while (temp == NULL);
    system("cls");
    successorPrediction(root, temp->info.nama);
    printf("\n\tPress any key to continue . . . ");
    getch();
    system("cls");
}


// Function untuk menghitung anggota keluarga yang masih hidup
// author: Alya Naila Putri Ashadilla
// I.S. : anggota keluarga yang masih hidup belum diketahui 
// F.S. : anggota keluarga yang masih hidup sudah diketahui
int countLivingFamilyMembers(address node) {
    int count = 0;
    if (node == NULL){ // Jika node kosong, maka akan mengembalikan nilai 0
        return 0;
    } else if(node->info.alive == true){ //jika status hidup node bersifat true maka nilai count akan bertambah
        count++;
    }

    //Menghitung jumlah anggota keluarga hidup pada node pasangan, anak, dan saudara
    count +=countLivingFamilyMembers(node->node_mate);
    count +=countLivingFamilyMembers(node->node_fs);
    count +=countLivingFamilyMembers(node->node_nb);

    return count;
}

// Fungsi untuk memprediksi pewaris takhta selanjutnya dari suatu node
// author: Alya
// I.S : nama pewaris takhta belum diketahui
// F.S : nama pewaris takhta telah diketahui
void successorPrediction(address root, infotype name) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    // Cari node dengan nama yang sesuai
    address current = search(root, name);;

    if (current == NULL) {
        printf("Person with name '%s' not found.\n", name); 
    }else {
        // Lakukan prediksi berdasarkan aturan penurunan tahta
        // Jika memiliki anak dan masih hidup, pewaris tahta adalah anak pertama yang masih hidup
        if ((current->node_fs != NULL) && (current->node_fs->info.alive == true)) {
            printf("Predicted heir: %s\n", current->node_fs->info.nama);
            return;
        }

        // Jika tidak memiliki anak tapi memiliki saudara, pewaris tahta adalah saudara pertama yang masih hidup
        if (current->node_nb != NULL) {
            address temp = current->node_nb;
            while (temp != NULL && temp->info.alive != true) {
                temp = temp->node_nb;
            }
            if (temp != NULL) {
                printf("Predicted heir: %s\n", temp->info.nama);
                return;
            }
        }

        // Cari pewaris tahta di antara saudara-saudara orang tua
        if (current->node_parrent != NULL && current->node_parrent->node_nb != NULL) {
            address temp = current->node_parrent->node_nb;
            while (temp != NULL && temp->info.alive != true) {
                temp = temp->node_nb;
            }
            if (temp != NULL) {
                    printf("Predicted heir: %s\n", temp->info.nama);
                    return;
            }

        }

        //Jika tidak ada saudara dari orang tua, cari pewaris tahta dari anak saudara orang tua
       if (current->node_parrent != NULL && current->node_parrent->node_nb != NULL) { 
            if(current->node_parrent->node_nb != current && current->node_parrent->node_nb->node_fs != NULL){
                address temp = current->node_parrent->node_nb;
                successorPrediction(temp, temp->info.nama);
                return;
            }
        }

        // Jika tidak ada sepupu, perlu untuk memeriksa di atas
        if (current->node_parrent != NULL && current->node_parrent->node_parrent != NULL) {
            address temp = current->node_parrent;
            while(temp != NULL && temp->info.alive != true) {
                temp = temp->node_parrent;
            } 
            if(temp != NULL){
                printf("Predicted heir: %s\n", temp->info.nama);
                return; 
            }
        }
            // Jika tidak ada pewaris tahta yang sesuai, maka tidak ada prediksi yang bisa dibuat.
            printf("No predicted heir found for %s.\n", name);
            return;
    }
}



void start(){
    system("cls");
    printf("\n\n");
	printf("\n\t\t\t\t                                        _____________                          ");
	printf("\n\t\t\t\t                                       |'+.   |   .+'|                         ");
	printf("\n\t\t\t\t                                       |___'+.|.+'___|                         ");
	printf("\n\t\t\t\t                                       |   .+'|'+.   |                         ");
	printf("\n\t\t\t\t                                       |.+'___|___'+.|                         ");
	printf("\n\t\t\t\t                                       |                                       ");
	printf("\n\t\t\t\t                                       |                                       ");
	printf("\n\t\t\t\t                                      / \\                                      ");
	printf("\n\t\t\t\t                                     /   \\                                     ");
	printf("\n\t\t\t\t                                    /     \\                                    ");
	printf("\n\t\t\t\t                                   /       \\                                   ");
	printf("\n\t\t\t\t                                  /         \\                                  ");
	printf("\n\t\t\t\t                              __ /  __   __  \\ __                              "); 
	printf("\n\t\t\t\t                             |  |__|  |_|  |__|  |                             ");
	printf("\n\t\t\t\t                             \\                   /                             ");
	printf("\n\t\t\t\t                          /\\  \\                 /  /\\                          ");
	printf("\n\t\t\t\t                         /  \\  \\_______________/  /  \\                         ");
	printf("\n\t\t\t\t                        /    \\  |   _     _   |  /    \\                        ");
	printf("\n\t\t\t\t                       /      \\ |  |_|   |_|  | /      \\                       ");
	printf("\n\t\t\t\t                      /________\\|_____________|/________\\                      ");
	printf("\n\t\t\t\t                      |         |   _     _   |         |                      ");
	printf("\n\t\t\t\t                      |   __    |  |_|   |_|  |    __   |                      ");
	printf("\n\t\t\t\t                      |  |__|   |_____________|   |__|  |                      ");
	printf("\n\t\t\t\t               _   _  |_        |   _     _   |        _|  _   _               ");
	printf("\n\t\t\t\t              | |_| |_| |_______|  |_|   |_|  |_______| |_| |_| |              ");
	printf("\n\t\t\t\t              |    _    |    __ |  __     __  | __    |    _    |              ");
	printf("\n\t\t\t\t     _   _   _|   |_|   |   |  |__|  |___|  |__|  |   |   |_|   |_   _   _     ");
	printf("\n\t\t\t\t    | |_| |_| |         |   |   __           __   |   |         | |_| |_| |    ");
	printf("\n\t\t\t\t    |         |    _    |   |  |__|         |__|  |   |    _    |         |    ");
	printf("\n\t\t\t\t    |    _    |   |_|   |   |       _______       |   |   |_|   |    _    |    ");
	printf("\n\t\t\t\t    |   |_|   |         |   |      |   |   |      |   |         |   |_|   |    ");
	printf("\n\t\t\t\t    |         |         |   |      |  0|0  |      |   |         |         |    ");
	printf("\n\t\t\t\t____|_________|_________|___|______|___|___|______|___|_________|_________|____");
	printf("\n\t\t   _  _   __   __   _   __    ___   _    _     ___   ____     ___   ____    __   _____   _____   __   __   _");
	printf("\n\t\t  | |/ / |  | |  \\ | | |  \\  |   | | \\  / |   |   | |  __|   |   \\ | __ \\  |  | |_   _| |  _  | |  | |  \\ | |");
	printf("\n\t\t  |   /  |  | |   \\| | | _ \\ | | | |  \\/  |   | | | | |__    | | / | || /  |  |   | |   | |_| | |  | |   \\| |");
	printf("\n\t\t  |   \\  |  | | |\\   | |   / | | | | |\\/| |   | | | |  __|   | | \\ | |\\ \\  |  |   | |   |  _  | |  | | |\\   |");
	printf("\n\t\t  |_|\\_\\ |__| |_| \\__| |__/  |___| |_|  |_|   |___| |_|      |___/ |_| \\_\\ |__|   |_|   |_| |_| |__| |_| \\__|");
    printf("\n\n\t\t\t\t\t\t\t    Press Enter To Continue");
    getchar();     //Menunggu untuk menekan enter
    system("cls"); // Membersihkan layar terminal
}

void Aturan()
{
    printf("\n\t\t__________________________________________________________________________________________________________________________________");
    printf("\n\t\t|I. Aturan penurunan tahta                                                                                                       |");
    printf("\n\t\t|   i. Pewaris tahta kerajaan adalah anak sulung (first son) dari keturunan langsung raja.                                       |");
    printf("\n\t\t|  ii. Aturan primogenetur absolut diterapkan, yang berarti bahwa putra dan putri yang berstatus sebagai anak sulung (first son) |");
    printf("\n\t\t|      sama-sama memenuhi syarat untuk menjadi pewaris tahta. Ini berarti pewaris tahta tidak dibatasi oleh gender.              |");
    printf("\n\t\t| iii. Dalam kondisi generasi terakhir, jika pewaris tahta (first son) meninggal maka tahta akan diwariskan ke anak selanjutnya  |");
    printf("\n\t\t|      (next brother) sebagai pewaris tahta urutan pertama.                                                                      |");
    printf("\n\t\t|  iv. Jika pewaris tahta tidak memiliki keturunan dan saudara kandungnya juga sudah meninggal, maka tahta dapat diwariskan      |");
    printf("\n\t\t|      kepada kerabat dekat terdekat yang masih hidup, seperti sepupu atau paman/ibunya.                                         |");
    printf("\n\t\t|                                                                                                                                |");
    printf("\n\t\t|II. Aturan penambahan anggota keluarga kerajaan                                                                                 |");
    printf("\n\t\t|   i. Raja / ratu pertama harus berumur antara 50 - 79                                                                          |");
    printf("\n\t\t|  ii. Untuk memiliki anak maka harus memiliki pasangan terlebih dahulu                                                          |");
    printf("\n\t\t| iii. Anak harus berumur minimal 19 tahun lebih muda dari orang tua                                                             |");
    printf("\n\t\t|  iv. Nama anak tidak boleh sama dengan anggota keluarga lain                                                                   |");
    printf("\n\t\t|                                                                                                                                |");
    printf("\n\t\t|III. Aturan penambahan pasangan anggota keluarga kerajaan                                                                       |");
    printf("\n\t\t|   i. Umur minimal untuk memiliki pasangan adalah 18 tahun                                                                      |");
    printf("\n\t\t|  ii. Umur minimal pasangan adalah 18 tahun                                                                                     |");
    printf("\n\t\t| iii. Pasangan harus berlawanan jenis                                                                                           |");
    printf("\n\t\t|  iv. Jumlah maksimal pasangan adalah 1                                                                                         |");
    printf("\n\t\t|   v. Nama pasangan tidak boleh sama dengan anggota keluarga lain                                                               |");
    printf("\n\t\t|                                                                                                                                |");
    printf("\n\t\t|IV. Aturan penghapusan anggota keluarga kerajaan                                                                                |");
    printf("\n\t\t|   i. Jika pohon keluarga kosong, tidak ada anggota keluarga yang dapat dihapus                                                 |");
    printf("\n\t\t|  ii. Jika anggota keluarga yang dihapus adalah daun (leaf) tanpa keturunan, maka dia akan dihapus langsung                     |");
    printf("\n\t\t| iii. Jika anggota keluarga yang dihapus memiliki saudara berikutnya (next brother), maka dia akan digantikan                   |");
    printf("\n\t\t|      oleh saudaranya tersebut.                                                                                                 |");
    printf("\n\t\t|  iv. Jika anggota keluarga yang dihapus adalah putra pertama (first son), maka putra pertama akan digantikan                   |");
    printf("\n\t\t|      oleh saudara berikutnya.                                                                                                  |");
    printf("\n\t\t|   v. Jika anggota keluarga yang dihapus adalah raja, maka tahtanya akan dipindahkan ke saudaranya.                             |");
    printf("\n\t\t|  vi. Anggota kerajaan yang dihapus beserta semua keturunannya, yaitu putra pertama dan saudara-saudaranya,                     |");
    printf("\n\t\t|      akan dihapus secara berurutan.                                                                                            |");
    printf("\n\t\t|________________________________________________________________________________________________________________________________|");
    printf("\n");
}

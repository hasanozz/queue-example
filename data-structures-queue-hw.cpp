/*********************************************************
**			İSTANBUL MEDENİYET ÜNİVERSİTESİ				**
**		MÜHENDİSLİK VE DOĞA BİLİMLERİ FAKÜLTESİ			**
**			BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ				**
**		  VERİ YAPILARI VE ALGORİTMALAR DERSİ			**
**														**
**			ÖĞRENCİ ADI: HASAN ÖZGÜR ÖZDEMİR			**
**			ÖĞRENCİ NUMARASI: 23120205090				**
**********************************************************/



#include <stdio.h>
#include <stdlib.h>


typedef struct node {
	int id;
	node* next;
};
node* root = NULL;	// sıranın başındaki düğümü tutar
node* son = NULL;	// sıranın sonundaki düğümü tutar


void enqueue(int id)
{
	if (root == NULL){	// sıra boşsa rootu oluşturur gelen kişiyi ilk sıraya ekler
		root = (node*)malloc(sizeof(node));
		root->id = id;
		root->next = NULL;
		son = root;		// sadece 1 eleman olduğu için root ve son aynı düğümü gösterir
		printf("ID%d siraya eklendi\n", id);
		return;
	}

	node* newNode = (node*)malloc(sizeof(node));
	newNode->id = id;

	if (id == 3){	// id=3 ise gelen kişi sıranın başına eklenir root değişir
		node* temp = root;
		root = newNode;
		root->next = temp;
		printf("ID%d siraya eklendi\n", id);
	}

	else if (id == 2){	// id=2 ise yarı öncelikli müşteridir en öndeki düğümün 2 arkasına yerleştirilir
		if (root->next == NULL) {	// kuyrukta sadece 1 kişi varsa hemen arkasına ekler
			root->next = newNode;
			newNode->next = NULL;
			son = son->next;
			printf("ID%d siraya eklendi\n", id);
			return;
		}

		else if (root->next->next == NULL) // kuyrukta sadece 2 kişi varsa en öndekinin 2 arkasına yerleştirir.
		{
			root->next->next = newNode;
			newNode->next = NULL;
			son = son->next;
			printf("ID%d siraya eklendi\n", id);
			return;
		}

		node* iter = root->next;
		while (iter->next->id == 3)		// en öndeki düğümün 2 arkasındaki düğümün idsi 3 ise ID3 daha öncelikli olduğundan iteri bir düğüm ileri taşır
			iter = iter->next;
		newNode->next = iter->next;
		iter->next = newNode;
		printf("ID%d siraya eklendi\n", id);
	}

	else if (id == 1) {		// id=1 ise sıranın sonuna ekler
		son->next = newNode;
		son = son->next;
		son->next = NULL;
		printf("ID%d siraya eklendi\n", id);
	}
}


void dequeue() {	// sıranın başındaki kişiyi çıkartır, root değişir.
	if (root == NULL) {
		printf("sirada kimse yok\n");
		return;
	}
	node* temp = root;
	root = root->next;
	printf("ID%d isleme alindi\n", temp->id);
	free(temp);
}


void print_Queue() {	// kuyruğu görüntülemek için
	if (root == NULL) {
		printf("kuyrukta kimse yok\n");
		return;
	}
	node* iter = root;
	printf("kuyrugun on kismi --> ");
	while (iter->next != NULL) {
		printf("ID%d-", iter->id);
		iter = iter->next;
	}
	printf("ID%d\n", iter->id);

}


int main()
{
	int islem = 0;

	while (islem != 4) {	// kullanıcı 4 girene kadar döngüyü devam ettir.
		printf("*********************************\n");
		printf("[1] Kisi Ekle\n[2] Islem Al\n[3] Kuyrugu Goruntule\n[4] Cikis\nYapmak istediginiz islem: ");
		scanf_s("%d", &islem);
		printf("*********************************\n");
		if (islem == 1) {
			int idNo;
			printf("\tID NUMARASI\n[1] Normal Musteri\n[2] Ozel Musteri\n[3] +65 Yas Ustu Musteri\nSeciminiz: ");
			scanf_s("%d", &idNo);
			enqueue(idNo);
		}
		else if (islem == 2)
			dequeue();

		else if (islem == 3)
			print_Queue();
	}


	return 0;
}
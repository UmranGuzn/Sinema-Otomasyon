#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum fiyat{
tam=30,
ogrenci=20
};

enum secim{
bilet=1,
doluluk_yonlendirme,
hasilat_yonlendirme,
devamet
};

enum salon_tip{
kirm=1,
mav,
yes
};

typedef struct{
int matine[5][50];
}mavi;

typedef struct{
int matine[5][50];
}yesil;

typedef struct{
int matine[5][50];
}kirmizi;

typedef struct{

    mavi m;
    yesil y;
    kirmizi k;
}salon;


int main()
{
    FILE *sifre,*sifre_kontrol;
    int k_sifre=1234,girilen_sifre;

    sifre=fopen("sifre.txt","w");
    fprintf(sifre,"%d",k_sifre);
    fclose(sifre);

    sifre_giris:

    printf("----------Sinema Bilet Otomasyonu----------\n");
    printf("\t\tHosgeldiniz!\n");
    printf("Lutfen Sifre Giriniz:\t");
    scanf("%d",&girilen_sifre);

    sifre_kontrol=fopen("sifre_kontrol.txt","w");
    fprintf(sifre_kontrol,"%d",girilen_sifre);
    fclose(sifre_kontrol);


    sifre=fopen("sifre.txt","r");
    sifre_kontrol=fopen("sifre_kontrol.txt","r");
    char sifre_eleman,kontrol_eleman;
    int ayni=0;

    while(sifre_eleman!=EOF){
        sifre_eleman=getc(sifre);
        kontrol_eleman=getc(sifre_kontrol);

        if(sifre_eleman==kontrol_eleman)
            continue;
        else{
            printf("Hatali Sifre Girisi!");
            goto sifre_giris;
        }
    }


    int yon,i,j,sayac,devam;
    salon s;

    for(i=0;i<5;i++){
        for(j=0;j<50;j++){
            s.k.matine[i][j]==0;
            s.m.matine[i][j]==0;
            s.y.matine[i][j]==0;
        }
    }

    int yenisecim=0;

    do{
        printf("Bilet satin almak icin --> 1 \n");
        printf("Doluluk Bilgisi icin   --> 2 \n");
        printf("Hasilat Bilgisi icin   --> 3 \n");
        scanf("%d",&yon);
        if(yon!= bilet && yon!=doluluk_yonlendirme && yon!=hasilat_yonlendirme){
            printf("Yanlis Secim Yaptiniz.. Lütfen Bekleyin Yönlendiriliyorsunuz..\n");
            goto sifre_giris;
        }
        if(yon==bilet)
            yenisecim=Bilet_Satis(bilet,yenisecim);
        if(yon==doluluk_yonlendirme)
           Bilet_Satis(doluluk_yonlendirme);
        if(yon==hasilat_yonlendirme)
            Hasilat(hasilat_yonlendirme);


            printf("Devam Etmek icin  4 sec\n");
            scanf("%d",&devam);
    }while(devam==devamet);
    printf("Cikis Yapiliyor...");


    return 0;
}

int Bilet_Satis(int yonlendirme,int dondurulen)
{

    FILE *doluluk,*hasilat1;
    salon s;

    int salon_no,matine_no;

    switch(yonlendirme){
case bilet:
    konum1:
        printf("Salon Seciniz:\nKirmizi icin --> 1 \nMavi icin --> 2 \nYesil icin -->3\n");
        scanf("%d",&salon_no);
        if(salon_no!=kirm&& salon_no!=mav&& salon_no!=yes)
            goto konum1;
        printf("Matine seciniz [1-5 arasi secim yapiniz]:  ");
        scanf("%d",&matine_no);

        switch(salon_no){
    case kirm:
        srand( time(NULL));
        int random=rand()%50;
        int *kirmizi_salon;
        kirmizi_salon=s.k.matine;
        int i=((matine_no-10)*50)+random;
        if( *(kirmizi_salon+i)!=1){
            *(kirmizi_salon+i)==1;

            printf("Kirmizi salon %d. matine %d. koltuk'a kayit yapildi.\n",matine_no,random);
            doluluk=fopen("doluluk.txt","a");
            fprintf(doluluk,"Kirmizi salon %d. matine %d. koltuk dolu.\n",matine_no,random);
            fclose(doluluk);

        }
        break;

    case mav:
        srand( time(NULL));
           int random2=rand()%50;
        int *mavi_salon;
        mavi_salon=s.m.matine;
        int f=((matine_no-10)*50)+random2;
        if( *(mavi_salon+f)!=1){
            *(mavi_salon+f)==1;

            printf("Mavi salon %d. matine %d. koltuk'a kayit yapildi.\n",matine_no,random2);
            doluluk=fopen("doluluk.txt","a");
            fprintf(doluluk,"Mavi salon %d. matine %d. koltuk dolu.\n",matine_no,random2);
            fclose(doluluk);


        }
        break;
    case yes:
          srand( time(NULL));
           int random3=rand()%50;
        int *yesil_salon;
        yesil_salon=s.y.matine;
        int h=((matine_no-10)*50)+random3;
        if( *(yesil_salon+h)!=1){
            *(yesil_salon+h)==1;

            printf("Yesil salon %d. matine %d. koltuk'a kayit yapildi.\n",matine_no,random3);
            doluluk=fopen("doluluk.txt","a");
            fprintf(doluluk,"Yesil salon %d. matine %d. koltuk dolu.\n",matine_no,random3);
            fclose(doluluk);

        }
        break;
        }

        return ucret(dondurulen);
        break;

    case doluluk_yonlendirme:
        doluluk=fopen("doluluk.txt","r");
        char kontrol;
        while(kontrol!=EOF){
            kontrol=getc(doluluk);
            putchar(kontrol);
        }
        fclose(doluluk);
        break;
    }
}

int ucret(int dondurulen){

    int sec,toplam_hasilat=dondurulen;
    printf("Ogrenci bileti icin -->1\nTam Bilet icin -->2\n");
    scanf("%d",&sec);
    if(sec==1){

        printf("Ogrenci Ucreti : 20 TL\n");
        toplam_hasilat+=ogrenci;
        Hasilat(toplam_hasilat);
        return toplam_hasilat;
    }
    else{
        printf("Tam Ucret : 30 TL\n");
        toplam_hasilat+=tam;
        Hasilat(toplam_hasilat);
        return toplam_hasilat;
    }


}


int Hasilat(int a){

FILE *hasilat;
if(a!=hasilat_yonlendirme){
    hasilat=fopen("hasilat.txt","w");
    fprintf(hasilat,"Hasilat: %d \n",a);
    fclose(hasilat);
}
 else{
     int ara;
    hasilat=fopen("hasilat.txt","r");
    do{
    ara=getc(hasilat);
    putchar(ara);
    }while(ara!=EOF);
    fclose(hasilat);
 }

}

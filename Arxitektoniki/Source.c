/* Evi Philippou & Maria Stylianou
	Ergastirio Arxitektonikis
		Ergasia Eksaminou*/

//orizw vivliothikes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<time.h>
#include<math.h>

// orizw tis sta8eres
#define Cache 32
#define Ram 1024
#define _CRT_SECURE_NO_DEPRECATE
#define size_word 4
#define direct_mapped 0
#define fully_associate 0
#define  N_way_set_associate 0
#define n_way 2
#define mainCRTStartup
#define megethos 3
#define words_block 2.0


//deiktes pou dixnoun stin prwti thesi tou file
FILE *header;
FILE *header2;
errno_t arxeio2;
errno_t arxeio;

int main()
{
	//orizw metavlites
	double cache=32;
	double ram=1024;
	double Size_word=4;
	double Direct_mapped=0;
	double Fully_associate=0;
	double n_way_set_associate=0;
	double N_way=1;
	double tag;
	double index;
	double block_offset;
	double lexeis;
	double set;
	int num=0;
	int num1;
	int xar;
	char charaxtiras;
	double dieuthinsi;
	int r=0;
	int w=1;
	int m=2;
	int f=3;
	int size;
	int type;
	int way;
	//counters
	int g;
	int v;
	int j;
	int h;
	int k;
	int i;
	int counter;
	//dimiourgia pinakwn
	char table[256];
	char pinakas[256];
	int diadikos[256];
	
	//periorismos
	if(Cache > Ram)
	{ 
		printf("i cache prepei na einai mikroteri tis ram, dokimase ksana :)");
		system("pause");
		return(1);
	}
	
	//ipologismos address bits
	dieuthinsi=(log(ram/size_word))/(log(2.0));
	
	//periorismos
	if(dieuthinsi > 256)
	{
		printf("adinato i dieuthinsi den mporei na kseperna tis kataxoriseis tou pinaka ");
		system("pause");
		return(1);
	}
	
	//anoigma file gia grapsimo (w)
	arxeio = fopen_s( &header, "arxitektoniki.txt","w+");
	arxeio2 = fopen_s( &header2, "output_file.txt","w+");

	//praksi gia ipologismo megethous tou file
	size= megethos * Cache;

    //emfanizei diaforetiko ari8mo ka8e fora pou trexei
	srand( (unsigned)time( NULL ) );
	
	//ksekina na eisagei dedomena mesa sto file
	for(i=0; i<size; i++)
	{
		//epilegei tixaia apo tous arithmous 0, 1, kai 2 pou antisoixoun sto r,w,m
		//i sinartisi rand dialegei tixaio ari8mo, periorizoume ton ari8mo mas %3
		//dld diairoume ton terastio ari8mo me to 3
		//kai to ipoloipo ipologizete apo 0 mexri 2
		xar = rand()%3 ;

		//anagnwrizei se ti anaferete ka8e arithmos gia na ta
		//gra4ei stin prwti stili tou arxeiou
		if (xar == 0)
			fprintf(header, "r\t");
		else if( xar == 1)
			fprintf(header, "w\t");
			else if (xar == 2)
				fprintf(header, "m\t");
				
		//epilegei tixaious ari8mous
		num = rand()%Ram/size_word;
		
		//arxikopiisi pinaka me 0 gia na dektei ta diadika bits
		for(v=0;v<dieuthinsi;v++)
		{
			diadikos[v]=0;
		}

		j=0;
		num1=num;

		//metatrepoume to num gia na to kanei diadiko kai na to gra4ei stin deuteri stili tou arxeiou
		while(num1!=0) 
			{
				diadikos[j]=num1%2;
				num1=num1/2;
				j++;
			}
		//gia na vroume ton periorismo gia to for
		h=(int)(dieuthinsi-1);
			//ksekinoume to tipoma apo panw pros ta katw gia na tipothei me tin swsti seira o arithmos kai oxi anapoda
			for(k=h;k>=0; k--)
				{
					fprintf(header,"%d",diadikos[k]);
				}
	
		fprintf( header, "\t");
		//tiponei diadiko arithmo
		fprintf( header, "%d\n", num);
	}
	//kleinoume to arxeio dedomenwn
	arxeio = fclose(header);
	
	//kathorizei o xristis ton tipo krifis mnimis apo ta define
   if((direct_mapped==1) &&(fully_associate==0) &&(N_way_set_associate==0))
	{

		//Direct Mapped:ipologismos block offset, index kai tag
		block_offset=(log(words_block))/(log(2.0));
		lexeis=(cache)/(size_word)/words_block;
		index=log(lexeis)/log(2.0);
		tag=(dieuthinsi-block_offset-index);
		printf("%lf - %lf -%lf   \n",tag,index,block_offset);
		arxeio = fopen_s( &header, "arxitektoniki.txt","r");

	
	//diavazoume apo to prwto file kai apothikeuoume se ena pinaka megalou megethous	
	while (fgets(pinakas,256,header) != NULL )
	{
		//arxikopiisi counter me 0 etsi wste na tiponoume sto deutero file swsta
		counter=0;
		//periiorismos
		for(k=0;k<(int)(dieuthinsi +2);k++)
		{
			//tiponoume tin prwti thesi tou pinaka pou einai m i r i w
			if(counter==0)
			{
				fprintf(header2,"%c", pinakas[0]);
				
			}
			//tiponei tin epomeni timi tou pinaka ara to \t
			if (counter==1)
			{
				fprintf(header2,"%c", pinakas[1]);
				
			}
			//tiponei ton diadiko arithmo
			if(counter>=2) 
			{
				//me vasi tous pio panw ipologismous afinoume kena anamesa sta bits tou diadikou arithmou
				//etsi wste na xwrisoume ta bits pou antistixoun sto tag, sto index(an iparxei) kai tou block offset
				fprintf(header2, "%c", pinakas[counter]);
				if (counter==tag+1)
				{fprintf(header2,"\t");}
			
				if (counter==tag+index+1)
				{fprintf(header2,"\t");}
				
				
				}
			//auksisi counter gia na parei oles tis times tou pinaka
			counter++;
		
		}
		//tiponei sto file 2
		fprintf(header2, "\n");
		
	}
	}
		
	else if((direct_mapped==0) &&(fully_associate==1) &&(N_way_set_associate==0)) 
	{
		// Fully Associate:ipologismos block offset kai tag mono epeidi sto fully associate den iparxei index
		block_offset=log(words_block)/log(2.0);
		index=0;
		tag=dieuthinsi-block_offset;
		printf("%lf - %lf -%lf   \n",tag,index,block_offset);
		arxeio = fopen_s( &header, "arxitektoniki.txt","r");

	while (fgets(pinakas,256,header) != NULL )
	{
		counter=0;
		for(k=0;k<(int)(dieuthinsi +2);k++)
		{
			if(counter==0)
			{
				fprintf(header2,"%c", pinakas[0]);
				
			}
			if (counter==1)
			{
				fprintf(header2,"%c", pinakas[1]);
				
			}
			if(counter>=2) 
			{
				fprintf(header2, "%c", pinakas[counter]);
				if (counter==tag+1)
				{fprintf(header2,"\t\t");}
			
				if (counter==tag+index+1)
				{fprintf(header2,"\t");}
				
				
			}
			counter++;
		
		}
		fprintf(header2, "\n");
	}
}
		// N- ways Set Associate: ipologismos block offset, index kai tag
		 else if((direct_mapped==0) &&(fully_associate==0) &&(N_way_set_associate==1))
		{

			block_offset=(log(words_block))/log(2.0);
			lexeis=((cache)/(size_word))/words_block;
			set=lexeis/n_way;
			index=log(set)/log(2.0);
			tag=dieuthinsi-index-block_offset;

			printf("%lf - %lf -%lf   \n",tag,index,block_offset);
			arxeio = fopen_s( &header, "arxitektoniki.txt","r");

		while (fgets(pinakas,256,header) != NULL )
		{
			counter=0;
			for(k=0;k<(int)(dieuthinsi +2);k++)
		{
			if(counter==0)
			{
				fprintf(header2,"%c", pinakas[0]);
				
			}
			if (counter==1)
			{
				fprintf(header2,"%c", pinakas[1]);
				
			}
			if(counter>=2) 
			{
				fprintf(header2, "%c", pinakas[counter]);
				if (counter==tag+1)
				{fprintf(header2,"\t");}
			
				if (counter==tag+index+1)
				{fprintf(header2,"\t");}
				
			}
			counter++;
		
		}
		fprintf(header2, "\n");
		
		}
	}
		//periorismoi gia tipo cache
			else if((direct_mapped==0) &&(fully_associate==0) &&(N_way_set_associate==0))
		{
			printf("Lathos eisagwgi\n");
		}
		 
		else if((direct_mapped==1) &&(fully_associate==1) &&(N_way_set_associate==0))
		{
			printf("Lathos eisagwgi\n");
		}
		
		else if((direct_mapped==0) &&(fully_associate==1) &&(N_way_set_associate==1))
		{
			printf("Lathos eisagwgi\n");
		}
		
		else if((direct_mapped==1) &&(fully_associate==1) &&(N_way_set_associate==1))
		{
			printf("Lathos eisagwgi\n");
		}
	//kleisimo arxeiwn 		
	arxeio = fclose(header);
	arxeio2 = fclose(header2);

	system("pause");
	return(0);
	}//end main
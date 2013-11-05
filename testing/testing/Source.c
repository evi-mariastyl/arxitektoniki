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
//orisame ta pio katw define gia na anagnwrisei to valid san 0 kai 1
#define false   0
#define true    1
#define bool int

//dilwsi struct list gia kathe typo cache
//sctuct gia to typo n-ways-set-associative
typedef struct list1
	{
		double tag;
		double set;
		double index;
		int dirty;
		bool valid;
		double block_offset;
	}nway;
nway *pointer1; // orisame ena deixti gia na mporoume na elegxoume ta stoixeia tou struct

//struct gia to typo direct-mapped 
typedef struct list2
{
	double tag;
	double index;
	double block_offset;
	int dirty;
	bool valid;
	}direct;
direct *pointer2;

	//struct gia to typo fully - associative
typedef struct list3
{
	double block_offset;
	double tag;
	double index;
	int dirty;
	bool valid;
	}fully;
fully *pointer3;

//deiktes pou dixnoun stin prwti thesi tou file
FILE *header;
FILE *header2;
FILE *header3;
errno_t arxeio;
errno_t arxeio2;
errno_t arxeio3;

int main()
{
	//orizw metavlites
	double cache=32;
	double ram=1024;
	double size_word=4;
	int direct_mapped=0;
	int fully_associate=0;
	int n_way_set_associate=0;
	double N_way=1;
	double tag;
	int check_tag;
	double index;
	int check_index;
	double block_offset;
	int check_blockoffset;
	double lexeis;
	double set;
	int no_write_allocate;
	int write_allocate;
	int write_through;
	int write_back;
	int read_from_cache;
	int read_from_ram;
	int write_to_cache;
	int write_to_ram;
	int num=0;
	int num1;
	int xar;
	double dieuthinsi;
	int r=0;
	int w=1;
	int m=2;
	int f=3;
	int size;
//	int type;
//	int way;
	int flush=5;
	int newline=0;
	int megethos;
	double words_block;
	int sinolikoi_kikloi;
	//counters
	int z;
	int g;
	int v;
	int j;
	int h;
	int k;
	int i;
	int test;
	int test2;
	int miss=0;
	int hit=0;
	int counter;
	int inflush;
	int inflush2;
	int counter_flush;
	int counterPar;
	char *token;
	char *token2;
	const char delimiter[2] = " ";
//	char *xaraxtiras;
	//dimiourgia pinakwn
	char miss_hit[256];
	char pinakas[256];
	int diadikos[256];
	char pinPar[256];

	counterPar=0;
	//anoigma file gia grapsimo (w) kai anoigma file gia diavasma (r)
	arxeio = fopen_s( &header, "arxitektoniki.txt","w+");
	arxeio2 = fopen_s( &header2, "output_file.txt","w+");
	//arxeio3= fopen_s(&header3, "arxeio_parametrwn","w");
    arxeio3= fopen_s(&header3, "arxeio_parametrwn","rt");

	// diavazontas apo to arxeio paramertwn arxikopoioume tis metavlites mas
	for(g=0;g<18;g++)
	{
		//ta stoixeia pou diavazei apothikevontai ston pinaka pinPar
		if(fgets(pinPar,256,header3)!= NULL)
			{
				token=strtok_s(pinPar,delimiter,&token2);
			switch (g)
			{
			case 0: cache=atof(token2);
				break;
			case 1: ram=atof(token2);
				break;
			case 2: size_word=atof(token2);
				break;
			case 3:	direct_mapped=atoi(token2);
				break;
			case 4: fully_associate=atoi(token2);
				break;
			case 5: n_way_set_associate=atoi(token2);
				break;
			case 6: N_way=atof(token2);
				break;
			case 7: flush=atoi(token2);
				break;
			case 8: megethos=atoi(token2);
				break;
			case 9: words_block=atof(token2);
				break;
			case 10: no_write_allocate=atoi(token2);
				break;
			case 11: write_allocate=atoi(token2);
				break;
			case 12: write_through=atoi(token2);
				break;
			case 13: write_back=atoi(token2);
				break;
			case 14: read_from_cache=atoi(token2);
				break;
			case 15: read_from_ram=atoi(token2);
				break;
			case 16: write_to_cache=atoi(token2);
				break;
			case 17: write_to_ram=atoi(token2);
				break;
			default: printf("Lathos");
				break;
			}
		}
	}
	//kleisimo arxeiou parametrwn
	arxeio3 = fclose(header3);

	//periorismos gia Ram kai Cache
	if(cache > ram)
	{ 
		printf("i cache prepei na einai mikroteri tis ram, dokimase ksana \n");
		system("pause");
		return(1);
	}
	//ipologismos address bits
	dieuthinsi=(log(ram/size_word))/(log(2.0));
	
	//periorismoos gia to megethos tis dieuthinsis
	if(dieuthinsi > 256)
	{
		printf("adinato i dieuthinsi den mporei na kseperna tis kataxoriseis tou pinaka \n");
		system("pause");
		return(1);
	}
	//periorismoi gia tis arxikopioisis pou dinontai gia ton ka8e typo cache
	if((direct_mapped<0)||(direct_mapped>1)) 
	{
		printf("To direct mapped mporei na einai i 0 i 1\n");
		system("pause");
		return(1);
	}
	if((fully_associate<0)||(fully_associate>1)) 
	{
		printf("To fully associate mporei na einai i 0 i 1\n");
		system("pause");
		return(1);
	}
	if((n_way_set_associate<0)||(n_way_set_associate>1)) 
	{
		printf("To n-way set associate mporei na einai i 0 i 1\n");
		system("pause");
		return(1);
	}
	// Elegxos gia to megethos tis Ram
	test= log(ram)/log(2.0);
	test2 = pow(2.0,test);
	if ( test2 != ram )
	{
		printf("To megethos tis Ram prepei na einai dinami tou 2\n");
		system("pause");
		return(1);
	}

	// Elegxos gia to megethos tis Cache
	test = log(cache)/log(2.0);
	test2 = pow(2.0,test);
	if (test2!= cache)
	{
		printf("To megethos tis Cache prepei na einai dinami tou 2");
		system("pause");
		return(1);
	}
	
	// Elegxos twn ari8mwn pou iparxoun se ka8e block
	test= log(words_block)/log(2.0);
	test2= pow(2.0,test);
	if (test2!= words_block )
	{
		printf("Oi lexeis ana block prepei na einai dinami tou 2");
		system("pause");
		return(1);
	}
	// Elegxos twn nway
	test= log(N_way)/log(2.0);
	test2= pow(2.0,test);
	if (test2!= N_way )
	{
		printf("To n-way prepei na einai dinami tou 2");
		system("pause");
		return(1);
	}
	//periorismoi gia tis prolitikes write
	if((write_through==1)&&(write_back==1)) 
{ 
	printf("den ginetai kai ta 2 na einai 1"); 
	system("pause"); 
	return(0); 
} 
	if((write_through==0)&&(write_back==0)) 
{ 
	printf("den ginetai kai ta 2 na einai 0"); 
	system("pause"); 
	return(0); 
} 
if((write_allocate==1)&&(no_write_allocate==1))
{
 	printf("den ginetai kai ta 2 na einai 1"); 
	system("pause");
 	return(0); 
} 
if((write_allocate==0)&&(no_write_allocate==0))
{
 	printf("den ginetai kai ta 2 na einai 0"); 
	system("pause");
 	return(0); 
} 
if((write_through<0)||(write_through>1)) 
{ 
	printf("den mporei na kseperna auta ta oria");
 	system("pause"); 
	return(0); 
} 
if((write_back<0)||(write_back>1)) 
{
 	printf("den mporei na kseperna auta ta oria"); 
	system("pause"); 
	return(0); 
} 
if((write_allocate<0)||(write_allocate>1)) 
{ 
	printf("den mporei na kseperna auta ta oria");
 	system("pause");
 	return(0);
 } 
if((no_write_allocate<0)||(no_write_allocate>1)) 
{
 	printf("den mporei na kseperna auta ta oria");
 	system("pause");
 	return(0); 
}
if(read_from_cache==0 || read_from_ram==0 || write_to_cache==0 || write_to_ram==0)
{
	printf("den mporoun oi kikloi na einai isi me 0");
 	system("pause");
 	return(0);
}
	//praksi gia ipologismo megethous tou file
	size= megethos * cache;

    //emfanizei diaforetiko ari8mo ka8e fora pou trexei
	srand( (unsigned)time( NULL ) );
	

	//ipologizoume to poso sixna tha emfanistei to flush
	if (flush!=0) 
		 {
			 inflush =(int) (size / flush); 
			 inflush2=inflush;
			 counter_flush=0;
			
		 }
	//ksekina na eisagei dedomena mesa sto file
	for(i=0; i<size; i++)
	{                             
        if(flush!=0)
		{
			if(counter_flush<=flush)
			{
				if(i==inflush2)
				{
					counter_flush++;
					xar=3;
					fprintf(header,"f\n");
					inflush2=inflush2+inflush;
					
				}
			}
		}
		//epilegei tixaia apo tous arithmous 0, 1, kai 2 pou antisoixoun sto r,w,m
		//i sinartisi rand dialegei tixaio ari8mo, periorizoume ton ari8mo mas %3
		//dld diairoume ton terastio ari8mo me to 3
		//kai to ipoloipo ipologizete apo 0 mexri 2
				xar = rand() % 3 ;
		
		//anagnwrizei se ti anaferete ka8e arithmos gia na ta
		//gra4ei stin prwti stili tou arxeiou
		if (xar == 0)
			fprintf(header, "r\t");
		else if( xar == 1)
			fprintf(header, "w\t");
			else if (xar == 2)
				fprintf(header, "m\t");
		//epilegei tixaious ari8mous
		num = rand()%(int)(ram/size_word);
		
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
   if((direct_mapped==1) &&(fully_associate==0) &&(n_way_set_associate==0))
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
		//periorismos
		for(k=0;k<(int)(dieuthinsi +2);k++)
		{
			//tiponoume tin prwti thesi tou pinaka pou einai m i r i w
			if(counter==0)
			{
				fprintf(header2,"%c", pinakas[0]);
				if(pinakas[0]=='f')
				{
					break;
				}
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
	//metatrepoume to diadiko ari8mo, gia to tag, se dekadiko
	check_tag=0;
	z=tag-1;
	for(i=0;i<tag;i++)
	{
		if(diadikos[i]==1)
			check_tag=check_tag+pow((double)2,z);
		z--;
	}
	//printf("%d",check_tag);
	//metatrepoume to diadiko ari8mo, gia to index, se dekadiko
	check_index=0;
	z=index-1;
	for(i=0;i<tag+index;i++)
	{
		if(diadikos[i]==1)
			check_index=check_index+pow((double)2,z);
		z++;
	}
	//printf("%d",check_index);
	//metatrepoume to diadiko ari8mo, gia to blockoffset, se dekadiko
	check_blockoffset=0;
	z=check_blockoffset-1;
	for(i=0;i<tag+index+block_offset;i++)
	{
		if(diadikos[i]==1)
			check_blockoffset=check_blockoffset+pow((double)2,z);
		z--;
	}
			//auksisi counter gia na parei oles tis times tou pinaka
			counter++;
		}

		//tiponei sto file 2
		fprintf(header2, "\n");
		//orizoume dinamika to megethos tis listas tou direct mapped
		pointer2=((direct*)malloc(lexeis*sizeof(direct)));
		//arxikopoisi ka8e komvou(grammis),diladi orizoume ola ta valid se 0 kai ta index pernoun tin timi tou metriti 
		for(k=0;k<lexeis;k++)
		{
			pointer2[k].valid=0;
			pointer2[k].index=k;
		}
		// an to action einai "r" kanei ta akolou8a
	if(pinakas[0]=='r')
	{
		for(k=0;k<lexeis;k++)
		{
			//an to valid einai 0 tote einai miss kai apo8ikevete ston pinaka miss_hit opou vriskontai ola ta apotelesmata
			if(pointer2[k].valid==0)
			{
				miss++;
				miss_hit[k]='Miss';
			}
			else if(pointer2[k].valid==1&&pointer2[k].index!=check_index)
			{
					miss++;
					miss_hit[k]='Miss';
			}
			else if((pointer2[k].valid==1&&pointer2[k].index==check_index) &&pointer2[k].tag!=check_tag)
				{
					miss++;
					miss_hit[k]='Miss';
				}
				else if(pointer2[k].valid==1 && pointer2[k].index==check_index &&pointer2[k].tag==check_tag &&pointer2[k].block_offset!=check_blockoffset)
				{						miss++;
										miss_hit[k]='Miss';			}
				else if((pointer2[k].block_offset==check_blockoffset)&&(pointer2[k].tag==check_tag) &&(pointer2[k].index==check_tag&& pointer2[k].valid==1))
				{
					hit++;	
					miss_hit[k]='Hit';}
	
			}
		}
	// an to action einai "w" kanei ta akolou8a
	if(pinakas[0]=='w')
	{
		for(k=0;k<lexeis;k++)
		{
			if(pointer2[k].index!=check_index)
			{
				miss++;
				pointer2[k].index=check_index;
				miss_hit[k]='Miss';
			}
			else if(pointer2[k].index==check_index && pointer2[k].valid==0)
			{
				miss++;
				pointer2[k].valid=1;
				miss_hit[k]='Miss';
			}
			else if(pointer2[k].index==check_index && pointer2[k].valid==1&&pointer2[k].tag!=check_tag)
			{
				miss++;
				pointer2[k].tag=check_tag;
				miss_hit[k]='Miss';
			}
			else if(pointer2[k].index==check_index && pointer2[k].valid==1&&pointer2[k].tag==check_tag &&pointer2[k].block_offset!=check_blockoffset)
			{
				miss++;
				pointer2[k].block_offset=check_blockoffset;
				miss_hit[k]='Miss';
			}
			else if(pointer2[k].index==check_index && pointer2[k].valid==1&&pointer2[k].tag==check_tag &&pointer2[k].block_offset==check_blockoffset)
			{
				hit++;
				miss_hit[k]='Hit';
			}
		}
	}
	//an to action einai "m" kanei to idio opws kai to "r"
	if(pinakas[0]=='m')
	{
		for(k=0;k<lexeis;k++)
		{
			if(pointer2[k].valid==0)
			{
				miss++;
				miss_hit[k]='Miss';
			}
			else if(pointer2[k].valid==1&&pointer2[k].index!=check_index)
			{
					miss++;
					miss_hit[k]='Miss';
			}
			else if((pointer2[k].valid==1&&pointer2[k].index==check_index) &&pointer2[k].tag!=check_tag)
				{
					miss++;
					miss_hit[k]='Miss';
				}
				else if(pointer2[k].valid==1 && pointer2[k].index==check_index &&pointer2[k].tag==check_tag &&pointer2[k].block_offset!=check_blockoffset)
				{						miss++;
										miss_hit[k]='Miss';
				}
				else if((pointer2[k].block_offset==check_blockoffset)&&(pointer2[k].tag==check_tag) &&(pointer2[k].index==check_tag&& pointer2[k].valid==1))
				{
					hit++;
					miss_hit[k]='Hit'; }
				
			}
		}
	// an to action einai "f" arxikopoiei ola ta valid me 0 kai ta index menoun ta idia
	if(pinakas[0]=='f')
	{
		for(k=0;k<lexeis;k++)
		{
			pointer2[k].valid=0;
			pointer2[k].index=k;
		}
	}
	//edw ekteloume tin poliki na einai write-through kai write allocate
	if(write_through==1 && write_allocate==1)
	{
		// an to apotelesma tou telikou pinaka miss_hit einai miss tote kanei tis kanei tis katalliles pra3eis
		//gia na ipologisei tous sinolikous kiklous
		if(*miss_hit=='Miss')
		{
			sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram+read_from_ram+write_to_cache;
		}
		else if(write_through==1 && no_write_allocate==1)
		{
			if(*miss_hit=='Miss')
			{
				sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram;}
		
			else 
			{
			sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram;
			}
		}
	}
	else if((write_through==1) && (no_write_allocate==1))
	if((write_back==1) && (write_allocate==1))
	{
		if(*miss_hit=='Miss'&&pointer2[check_index].dirty==1)
		{
			sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram+read_from_ram+write_to_cache;
		}
		else
		{
			sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram;
			pointer2[check_index].dirty=1;
		}
	}
	else if (write_back==1 && no_write_allocate==1)
	{
		if (*miss_hit== 'Miss')
			sinolikoi_kikloi = write_to_cache + write_to_ram + write_to_cache;
			else 
			{
				sinolikoi_kikloi = write_to_cache;
				pointer2[check_index].dirty = 1;
			}
	}
	}
	}	
	else if((direct_mapped==0) &&(fully_associate==1) &&(n_way_set_associate==0)) 
	{
		// Fully Associate:ipologismos block offset kai tag mono epeidi sto fully associate den iparxei index
		block_offset=log(words_block)/log(2.0);
		index=0;
		tag=dieuthinsi-block_offset;
		lexeis=(cache)/(size_word)/words_block;
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
				if(pinakas[0]=='f')
				{
					break;
				}
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
			//arxikopoisi ka8e komvou(grammis),diladi orizoume ola ta valid se 0 kai ta index pernoun tin timi tou metriti 
			pointer3=((fully*)malloc(lexeis*sizeof(fully)));
		for(k=0;k<lexeis;k++)
		{
			pointer3[k].valid=0;
			pointer3[k].index=k;
		}
		}
		fprintf(header2, "\n");
	}

}
		// N- ways Set Associate: ipologismos block offset, index kai tag
		 else if((direct_mapped==0) &&(fully_associate==0) &&(n_way_set_associate==1))
		{

			block_offset=(log(words_block))/log(2.0);
			lexeis=((cache)/(size_word))/words_block;
			set=lexeis/N_way;
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
				if(pinakas[0]=='f')
				{
					break;
				}
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
				//apo8ikevei to index mesa ston pinaka table
				if (counter==tag+index+1)
				{fprintf(header2,"\t");}
				

			}
			counter++;
			//arxikopoisi ka8e komvou(grammis),diladi orizoume ola ta valid se 0 kai ta index pernoun tin timi tou metriti 
			pointer1=((nway*)malloc(lexeis*sizeof(nway)));
		for(k=0;k<lexeis;k++)
		{
			pointer1[k].valid= 0;
			pointer1[k].index=k;
		}
		}
			
		fprintf(header2, "\n");
		
		}
	}
		//periorismoi gia tipo cache
			else if((direct_mapped==0) &&(fully_associate==0) &&(n_way_set_associate==0))
		{
			printf("Lathos eisagwgi\n");
		}
		 
		else if((direct_mapped==1) &&(fully_associate==1) &&(n_way_set_associate==0))
		{
			printf("Lathos eisagwgi\n");
		}
		
		else if((direct_mapped==0) &&(fully_associate==1) &&(n_way_set_associate==1))
		{
			printf("Lathos eisagwgi\n");
		}
		
		else if((direct_mapped==1) &&(fully_associate==1) &&(n_way_set_associate==1))
		{
			printf("Lathos eisagwgi\n");
		}

	
	//kleisimo arxeiwn 		
	arxeio = fclose(header);
	arxeio2 = fclose(header2);

	system("pause");
	return(0);
	}//end main
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
//struct gia to typo n-ways-set-associative
typedef struct list1
	{
		double tag;
		double set;
		double index;
		int dirty;
		int ilikia;
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
	int ilikia;
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
	double index;
	double block_offset;
	double lexeis;
	double set;
	int num=0;
	int num1;
	int xar;
	int dieuthinsi;
	int r=0;
	int w=1;
	int m=2;
	int f=3;
	int size;
	int miss=0;
	int hit=0;
	int flush=5;
	int newline=0;
	int megethos;
	double words_block;
	int sinolikoi_kikloi=0;
	int lru;
	int fifo;
	int max_ilikia=1000;
	int min_ilikia=0;
	//counters
	int g;
	int v;
	int j;
	int h;
	int k;
	int i;
//	int counter;
	int inflush;
	int inflush2;
	int counter_flush;
	int counterPar;
	int test;
	int test2;
	int no_write_allocate;
	int write_allocate;
	int write_back;
	int write_through;
	int read_from_cache;
	int read_from_ram;
	int write_to_cache;
	int write_to_ram;
	int check_tag;
	int check_index;
	int check_blockoffset;
	int z;
	char *token;
	char *token2;
	const char delimiter[2] = " ";
	//dimiourgia pinakwn
	int table[256];
	char *miss_hit[256];
	char *typos_miss[256];
	char pinakas[256];
	int diadikos[256];
	char pinPar[256];
	
	counterPar=0;
	//anoigma file gia grapsimo (w) kai anoigma file gia diavasma (r)
	arxeio = fopen_s( &header, "arxitektoniki.txt","w+");
	arxeio2 = fopen_s( &header2, "output_file.txt","w+");
//arxeio3= fopen_s(&header3, "arxeio_parametrwn","w");
    arxeio3= fopen_s(&header3, "arxeio_parametrwn","rt");

	//kanoume parsing tou file "arxeio_parametrwn" kai arxikopioume tis metavlites mas
	for(g=0;g<20;g++)
	{
		if(fgets(pinPar,256,header3)!= NULL)
			{
				//stin metavliti token2 apothikevete i parametros pou vriskete meta to keno
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
			case 18: lru=atoi(token2);
				break;
			case 19: fifo=atoi(token2);
				break;
			default: printf("Lathos");
				break;
			}
		}
	}
	//periorismoi gia tis prolitikes write
	if((write_through==1)&&(write_back==1)) 
	{ 
		printf("den ginetai kai ta 2 na einai 1"); 
		system("pause"); 
		return(0); 
	} 
	if((write_allocate==1)&&(no_write_allocate==1))
	{
 		printf("den ginetai kai ta 2 na einai 1"); 
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
	//ipologismos address bits
	dieuthinsi=(log(ram/size_word))/(log(2.0));
	//periorismos
	if(dieuthinsi > 256)
	{
		printf("adinato i dieuthinsi den mporei na kseperna tis kataxoriseis tou pinaka ");
		system("pause");
		return(1);
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
		//tiponei dekadiko arithmo
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
		//to for() 8a ekteleite 3 fores, tin prwto fora 8a ginete gia tin prwti 8esi tou pinaka[]
		//tin deuteri fora gia tin deuteri 8esi tou pinaka[], diladi to "\t"
		//tin triti fora gia ola bits tis dieuthinsi 
		for(k=0;k<3;k++) 
		{
			//tiponoume tin prwti thesi tou pinaka pou einai m i r i w
			if(k==0)
			{
				fprintf(header2,"%c", pinakas[0]);
				if(pinakas[0]=='f')
				{
					break;
				}
			}
			//tiponei tin epomeni timi tou pinaka ara to \t
			if (k==1)
			{
				fprintf(header2,"%c", pinakas[1]);
			}
			//tiponei ton diadiko arithmo
		if(k==2 && pinakas[0]!= 'f') 
			{
				// to z mas voi8a stin apo8ikeusi tou diadikou se interger kai oxi se charaxtira
				z=0;
				for (j=2;j<dieuthinsi+2;j++)			
						{
							if(pinakas[j]=='0')
							{
								table[z]=0;
								z++;
							}
							else if(pinakas[j]=='1')
							{
								table[z]=1;
								z++;
							}
						fprintf(header2,"%c", pinakas[j]);
						//me vasi tous pio panw ipologismous afinoume kena anamesa sta bits tou diadikou arithmou
						//etsi wste na xwrisoume ta bits pou antistixoun sto tag, sto index(an iparxei) kai tou block offset
						if (j==tag+1)
                                {fprintf(header2,"\t");}
                        
                                if (j==tag+index+1)
                                {fprintf(header2,"\t");}
						}//kleisimo for gia metatropi twn xharaxtirwn tou diadikou se ari8mous
						 // kai xwrismos twn bits

							//Ipologizei ta dekadika
							z=tag-1;
							check_tag=0;
							for (j=0;j<tag;j++)	// edw ipologizei se dekadiko ta bits tou tag
												//kai ta apo8ikevei sto check_tag
							{
								if(table[j]==1)
								check_tag=check_tag+pow(2.0,z);	
							z--;				
							}
							z=index-1;
							check_index=0;
							for(j=tag; j<tag+index; j++)// edw ipologizei se dekadiko ta bits tou index
														//kai ta apo8ikevei sto check_index
							{
								if(table[j]==1)
								check_index=check_index+pow(2.0,z);	
							z--;
							}
							z=block_offset-1;
							check_blockoffset=0;
						
							for(j=tag+index; j<tag+index+block_offset; j++)	// edw ipologizei se dekadiko ta bits tou block_offset
																	//kai ta apo8ikevei sto check_blockoffset
							{
								if(table[j]==1)
								check_blockoffset=check_blockoffset+pow(2.0,z);	
							z--;
							}
						}// kleisimo if() an to k==2
			
		}//kleisimo for() gia parsing tou arxeio dedomenwn(arxitektoniki.txt)
		
		//orizoume dinamika to megethos tis listas tou direct mapped
		pointer2=((direct*)malloc(lexeis*sizeof(direct)));
		//arxikopoisi ka8e komvou(grammis),diladi orizoume ola ta valid se 0 kai ta index pernoun tin timi tou metriti 
		for(k=0;k<lexeis;k++)
		{
			pointer2[k].valid=0;
			pointer2[k].index=k;
		}
		// an to action einai "m" kanei ta akolou8a
	if(pinakas[0]=='m')
	{
		for(k=0;k<lexeis;k++)
		{
			//an to index pou girevoume iparxei ginete elegxos gia valid,tag kai block_offset
			if(pointer2[k].index==check_index)
			{
				//an to valid einai 0 tote einai miss kai apo8ikevete ston pinaka miss_hit opou vriskontai ola ta apotelesmata
				if(pointer2[k].valid==0)
				{
					*miss_hit="Miss";
					*typos_miss="Compulsory";
					miss++;
				}
				// an to valid einai 1 tote eleg3e gia to tag
				else if(pointer2[k].tag==check_tag)// an to to tag isoutai tote eleg3e gia to block_offset
				{
				if(block_offset>0)// an to block_offset iparxei(diladi >0)
				{
					if(pointer2[k].block_offset==1) // an to block_offset einai 1 dld iparzei tote einai hit
					{
						*miss_hit="Hit";
						hit++;
					}
					else// an to block_offset einai diaforetiko tote einai miss
					{
						*miss_hit="Miss";
						*typos_miss="Capasity";
						miss++;
					}
				}
				else// an den iparxei block_offset tote einai hit afou to tag kai to index isountai me ekeina pou 4axnoumai kai to valid=1
				{
					*miss_hit="Hit";
					hit++;
				}
			}
			else //an to tag einai diaforetiko einai miss
			{
				*miss_hit="Miss";
				*typos_miss="Conflict";
				miss++;
			}
		
		}
	}
	}
	sinolikoi_kikloi=0;
	// an to action einai "w"  i "r" kanei ta akolou8a
	if(pinakas[0]=='w'|| pinakas[0]=='r')
	{
		for(k=0;k<lexeis;k++)
		{
			//an to index isoutai me ekeino pou girevoume
			if(pointer2[k].index==check_index)
			{
				if(pointer2[k].valid==0)//an to valid=0 den iparxei ara einai miss
				{
					*miss_hit="Miss";
					*typos_miss="Compulsory";
					miss++;
					pointer2[k].tag=check_tag;
					pointer2[k].block_offset=check_blockoffset;
					pointer2[k].valid=1;
				}
				else if(pointer2[k].tag==check_tag)// an kai to tag isoutai tote elegxoume kai to blockoffset
				{ 
				if(block_offset>0)// an iparxei block_offset 
				{
					if(pointer2[k].block_offset==check_blockoffset)// an to index isoutai tote einai hit
					{
						*miss_hit="Hit";
						hit++;
					}
					else// an den isoutai to block_offset tote einai miss
					{
						*miss_hit="Miss";
						*typos_miss="Capasity";
						miss++;
						pointer2[k].tag=check_tag;
						pointer2[k].block_offset=check_blockoffset;
						pointer2[k].valid=1;
					}
				}
				else// an den iparxei block_offset tote einai hit
				{
					*miss_hit="Hit";
					hit++;
				}
			}
					else// an to tag einai diaforetiko tote einai miss
					{
						*miss_hit="Miss";
						*typos_miss="Conflict";
						miss++;
						pointer2[k].tag=check_tag;
						pointer2[k].block_offset=check_blockoffset;
						pointer2[k].valid=1;
					}
				}//kleisimo tou if() gia to index
			}//kleisimo for() gia elegxo tou arxeiou

	//edw ekteloume tin poliki na einai write-through kai write allocate
	if(write_through==1 && write_allocate==1)
	{
		// an to apotelesma tou telikou pinaka miss_hit einai miss tote kanei tis kanei tis katalliles pra3eis
		//gia na ipologisei tous sinolikous kiklous
		if(*miss_hit=="Miss")
		{
			sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram+read_from_ram+write_to_cache;
		}
		else 
		{
			if(*miss_hit=="Hit")
			{
				sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram;
			}
			
		}//kleisimo gia ston *miss_hit iparxei "Hit"
	}// kleisimo gia to write_through kai write_allocate
	else if((write_through==1) && (no_write_allocate==1))
	{
		if(*miss_hit=="Miss")
		{
			sinolikoi_kikloi=sinolikoi_kikloi+ write_to_cache +write_to_ram;
		}
		else//an einai "Hit"
			sinolikoi_kikloi=sinolikoi_kikloi+write_to_ram;
	}// kleisimo gia to write_through==1 kai no_write_allocate
		else if (write_back==1 && write_allocate==1)
		{
			if (*miss_hit== "Miss")
				if(pointer2[check_index].dirty==1)
				{
					sinolikoi_kikloi =sinolikoi_kikloi+ write_to_cache + write_to_ram + read_from_ram;
				}
				else 
				{
					sinolikoi_kikloi = write_to_cache;
					pointer2[check_index].dirty = 1;
				}
		}// kleisimo gia to write_back kai write_allocate
		else if(write_back==1 && no_write_allocate==1)
		{
			if(*miss_hit=="Miss")
			{
				sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram;
			}
			else 
			{
				sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache;
				pointer2[check_index].dirty=1;
			}
		}// kleisimo gia to write_back kai no_write_allocate
	
	else
	{
		if(*miss_hit=="Miss")
		
			sinolikoi_kikloi=sinolikoi_kikloi+read_from_cache+read_from_ram;
		
		else
			sinolikoi_kikloi=sinolikoi_kikloi+read_from_cache;
	}
	}//kleisimo an to actio einai "w" i "r"

	// an to action einai "f" arxikopoiei ola ta valid me 0 kai ta index menoun ta idia
	if(pinakas[0]=='f')
	{
		for(k=0;k<lexeis;k++)
		{
			pointer2[k].valid=0;
			pointer2[k].index=k;
		}
	}// kleisimo an to action 'f'

	printf("\n");
	printf("Tag = %d\n",check_tag);
	printf("Index = %d\n",check_index);
	printf("Block Offset = %d\n",check_blockoffset);
	printf("Sinolikoi Kikloi = %d\n", sinolikoi_kikloi);
	//typwma sto output_file
	if(pinakas[0]!='f')
	{
		fprintf(header2,"\t%s",*miss_hit);
		if(*miss_hit=="Miss")
		{
			fprintf(header2,"\t%s",*typos_miss);
		}
	
	fprintf(header2, "\n");
	}
	else
		fprintf(header2, "\n");
	}//kleisimo while() pou diavazei apo to arxeio dedomenwn
	printf("Oi epitixeis prospa8ies einai %d\n",hit);
	printf("Oi apotixeis prospa8ies einai %d\n", miss);
	}// kleisimo tou if() gia direct mapped
	else if((direct_mapped==0) &&(fully_associate==1) &&(n_way_set_associate==0)) 
	{
		// Fully Associate:ipologismos block offset kai tag mono epeidi sto fully associate den iparxei index
		block_offset=log(words_block)/log(2.0);
		index=0;
		lexeis=(cache)/(size_word)/words_block;
		tag=dieuthinsi-block_offset;
		printf("%lf - %lf -%lf   \n",tag,index,block_offset);
		arxeio = fopen_s( &header, "arxitektoniki.txt","r");

	while (fgets(pinakas,256,header) != NULL )
	{
		//to for() 8a ekteleite 3 fores, tin prwto fora 8a ginete gia tin prwti 8esi tou pinaka[]
		//tin deuteri fora gia tin deuteri 8esi tou pinaka[], diladi to "\t"
		//tin triti fora gia ola bits tis dieuthinsi 
		for(k=0;k<3;k++) 
		{
			// typwnoume tin prwti 8esi tou pinaka pou einai to action
			if(k==0)
			{
				fprintf(header2,"%c", pinakas[0]);
				if(pinakas[0]=='f')
				{
					break;
				}
			}
			//tiponei tin epomeni timi tou pinaka ara to \t
			if (k==1)
			{
				fprintf(header2,"%c", pinakas[1]);
			}
			
		if(k==2 && pinakas[0]!='f') 
			{
				// to z mas voi8a stin apo8ikeusi tou diadikou se interger kai oxi se charaxtira
				z=0;
				for (j=2;j<dieuthinsi+2;j++)			
						{
							if(pinakas[j]=='0')
							{
								table[z]=0;
								z++;
							}
							else if(pinakas[j]=='1')
							{
								table[z]=1;
								z++;
							}
						fprintf(header2,"%c", pinakas[j]);
						//me vasi tous pio panw ipologismous afinoume kena anamesa sta bits tou diadikou arithmou
						//etsi wste na xwrisoume ta bits pou antistixoun sto tag, sto index(an iparxei) kai tou block offset
							if (j==tag+1)
								{fprintf(header2,"\t");}
                       
								if (j==tag+index+1)
								{fprintf(header2,"\t");}
						}
							//Ipologizei ta dekadika
								z=tag-1;
								check_tag=0;
								for (j=0;j<tag;j++)	//ipologizei se dekadiko ta bits gia to tag kai to apo8ikevei sto check_tag
								{
									if(table[j]==1)
										check_tag=check_tag+pow(2.0,z);	
									z--;				
								}
								z=index-1;
								check_index=0;
								for(j=tag; j<tag+index; j++)// ipologizei se dekadiko ta bits gia to index kai to apo8ikevei sto check_index
								{
									if(table[j]==1)
										check_index=check_index+pow(2.0,z);	
									z--;
								}
								z=block_offset-1;
								check_blockoffset=0;

								for(j=tag+index; j<tag+index+block_offset; j++)	//ipologizei se dekadiko ta bits gia to block_offset kai to apo8ikevei sto check_blockoffset
								{
									if(table[j]==1)
										check_blockoffset=check_blockoffset+pow(2.0,z);	
									z--;
								}
		
		//arxikopoisi ka8e komvou(grammis),diladi orizoume ola ta valid se 0 kai ta index pernoun tin timi tou metriti 
		pointer3=((fully*)malloc(lexeis*sizeof(fully)));
		for(k=0;k<lexeis;k++)
			{
				pointer3[k].valid=0;
				pointer3[k].index=k;
			}
			// an to action einai "m" kanei ta akolou8a
		if(pinakas[0]=='m')
		{
			for(k=0;k<lexeis;k++)
			{
				//an to valid einai 0 tote einai miss kai apo8ikevete ston pinaka miss_hit opou vriskontai ola ta apotelesmata
					if(pointer3[k].valid==0)
					{
						*miss_hit="Miss";
						*typos_miss="Compulsory";
						miss++;
					}
				
				else if(pointer3[k].valid==1)
				{
					if(pointer3[k].tag==check_tag)// an to tag isoutai me ekeino pou 8eloume tote elegxei gia block_offset
					{
						if(block_offset>0)// an iparxei block_offset
						{
							if(pointer3[k].block_offset==check_blockoffset)// an isoutai me ekeino pou 8eloume tote einai hit
							{
								*miss_hit="Hit";
								hit++;
							}
						
							else// an den isoutai to block_offset tote einai miss
							{
								*miss_hit="Miss";
								*typos_miss="Capasity";
								miss++;
							}
						}
						else// an den iparxei block_offset tote einai hit
						{
							*miss_hit="Hit";
							hit++;
						}
					}
				else// an to tag den einai to idio tote einai miss
				{
					*miss_hit="Miss";
					*typos_miss="Conflict";
					miss++;
				}
			}// kleisimo gia to if() an to valid=1
		}// kleisimo gia to for() tou parsing
		}//an to action einai "m"
		// an to action einai "w" i "r" kanei ta akolou8a
		if(pinakas[0]=='w'|| pinakas[0]=='r')
		{
			for(k=0;k<lexeis;k++)
			{
				if(pointer3[k].valid==0)// an to valid=0 tote den iparxei kai einai miss
					{
						*miss_hit="Miss";
						*typos_miss="Compulsory";
						miss++;
						pointer3[k].tag=check_tag;
						pointer3[k].block_offset=check_blockoffset;
						pointer3[k].valid=1;
					}
						else if(pointer3[k].valid==1)
						{
							if(pointer3[k].tag=check_tag)// an to tag isoutai me ekeino pou zitoume elegxoume gia block_offset
								{
								if(block_offset>0)// iparxei block_offset
								{
									if(pointer3[k].block_offset==check_blockoffset)// otan isoutai to block_offset tote einai hit
									{
										*miss_hit="Hit";
										hit++;
									}
									else// an den isoutai to block_offset tote einai miss
									{
										*miss_hit="Miss";
										*typos_miss="Capasity";
										miss++;
										pointer3[k].tag=check_tag;
										pointer3[k].block_offset=check_blockoffset;
										pointer3[k].valid=1;
									}
								}
							else// an den iparxei to block_offset tote einai hit
								{
									*miss_hit="Hit";
									hit++;
								}
							}
						
						else// an to tag einai diaforetiko einai miss
						{
							*miss_hit="Miss";
							*typos_miss="Conflict";
							miss++;
							pointer3[k].tag=check_tag;
							pointer3[k].block_offset=check_blockoffset;
							pointer3[k].valid=1;
						}
				}//kleisimo an to valid=1
			}// kleisimo tou for() gia parsing apo to arxeio

		//edw ekteloume tin poliki na einai write-through kai write allocate
		if(write_through==1 && write_allocate==1)
		{
			// an to apotelesma tou telikou pinaka miss_hit einai miss tote kanei tis kanei tis katalliles pra3eis
			//gia na ipologisei tous sinolikous kiklous
			if(*miss_hit=="Miss")
			{
				sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram+read_from_ram+write_to_cache;
			}
			else 
			{
				if(*miss_hit=="Hit")
				{
					sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram;
				}	
			}
		}// kleisimo an einai write_through kai write_allocate
		else if((write_through==1) && (no_write_allocate==1))
		{
			if(*miss_hit=="Miss")
			
				sinolikoi_kikloi=sinolikoi_kikloi+ write_to_cache +write_to_ram;
			
			else
				sinolikoi_kikloi=sinolikoi_kikloi+write_to_ram;
		}// kleisimo an einai write_through kai no_write_allocate
			else if (write_back==1 && write_allocate==1)
			{
				if (*miss_hit== "Miss")
					if(pointer3[check_index].dirty==1)
					{
						sinolikoi_kikloi =sinolikoi_kikloi+ write_to_cache + write_to_ram + read_from_ram;
					}
					else 
					{
						sinolikoi_kikloi = write_to_cache;
						pointer3[check_index].dirty = 1;
					}
			}// kleisimo an einai write_back kai write_allocate
			else if(write_back==1 && no_write_allocate==1)
			{
				if(*miss_hit=="Miss")
				{
					sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram;
				}
				else 
				{
					sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache;
					pointer3[check_index].dirty=1;
				}
			}// kleisimo an einai write_back kai no_write_allocate
		else
		{
			if(*miss_hit=="Miss")
		
				sinolikoi_kikloi=sinolikoi_kikloi+read_from_cache+read_from_ram;
		
			else
				sinolikoi_kikloi=sinolikoi_kikloi+read_from_cache;
		}
	}//kleisimo an to actio einai "w" kai "r"
		// an to action einai "f" arxikopoiei ola ta valid me 0 kai ta index menoun ta idia
		if(pinakas[0]=='f')
		{
			for(k=0;k<lexeis;k++)
			{
				pointer3[k].valid=0;
				pointer3[k].index=k;
			}
		}//kleisimo an to action einai 'f'
		
	}// kleisimo tou if() an to k=2
}// kleisimo tou for() gia to parsing tou arxeiou
		printf("\n");
		printf("Tag = %d\n",check_tag);
		printf("Index = %d\n",check_index);
		printf("Block Offset = %d\n",check_blockoffset);

if(pinakas[0]!='f')
{
	fprintf(header2,"\t%s",*miss_hit);
	if(*miss_hit=="Miss")
	{
		fprintf(header2,"\t%s", *typos_miss);
	}
	
	fprintf(header2, "\n");
}
}//kleisimo gia to while(pou diavazei to arxeio dedomenwn )
printf("Oi epitixeis prospa8ies einai %d\n",hit);
	printf("Oi apotixeis prospa8ies einai %d\n", miss);
}// kleisimo tou if() gia fully associate

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
		
			//periiorismos
			for(k=0;k<3;k++) 
			{
				//tiponoume tin prwti thesi tou pinaka pou einai m i r i w
				if(k==0)
				{
					fprintf(header2,"%c", pinakas[0]);
					if(pinakas[0]=='f')
					{
						break;
					}
				}
				//tiponei tin epomeni timi tou pinaka ara to \t
				if (k==1)
				{
					fprintf(header2,"%c", pinakas[1]);
				}
				//tiponei ton diadiko arithmo
			if(k==2 && pinakas[0]!='f') 
				{
					//me vasi tous pio panw ipologismous afinoume kena anamesa sta bits tou diadikou arithmou
					//etsi wste na xwrisoume ta bits pou antistixoun sto tag, sto index(an iparxei) kai tou block offset
					z=0;
						for (j=2;j<dieuthinsi+2;j++)			
								{
									if(pinakas[j]=='0')
									{
										table[z]=0;
										z++;
									}
									else if(pinakas[j]=='1')
									{
										table[z]=1;
										z++;
									}
									fprintf(header2,"%c", pinakas[j]);
									if (j==tag+1)
										{fprintf(header2,"\t");}
                        
										if (j==tag+index+1)
										{fprintf(header2,"\t");}
								}
			
									//Ipologizei ta dekadika
							
										z=tag-1;
										check_tag=0;
										for (j=0;j<tag;j++)			//epilegei apo ti thesi 2 mexri ti thesi Tag+1 gia tin epilogi tou tag
										{
											if(table[j]==1)
												check_tag=check_tag+pow(2.0,z);	
											z--;				
										}
										z=index-1;
										check_index=0;
										for(j=tag; j<tag+index; j++)	//epilegei ta bits apo ti thesi Tag+2 mexri tin Tag+index+1 gia index
										{
											if(table[j]==1)
												check_index=check_index+pow(2.0,z);	
											z--;
										}
										z=block_offset-1;
										check_blockoffset=0;

										for(j=tag+index; j<tag+index+block_offset; j++)	//epilegei ta bits tag +index +2 mexri tag +index+block_oofset +1 gia block_offset
										{
											if(table[j]==1)
												check_blockoffset=check_blockoffset+pow(2.0,z);	
											z--;
										} 
			}
				//orizoume dinamika to megethos tis listas tou direct mapped
		pointer1=((nway*)malloc(lexeis*sizeof(nway)));
		//arxikopoisi ka8e komvou(grammis),diladi orizoume ola ta valid se 0 kai ta index pernoun tin timi tou metriti 
		for(k=0;k<lexeis;k++)
		{
			pointer1[k].valid=0;
			pointer1[k].index=k;
		}
		// an to action einai "m" kanei ta akolou8a
	if(pinakas[0]=='m')
	{
		for(k=0;k<lexeis;k++)
		{
			//an to valid einai 0 tote einai miss kai apo8ikevete ston pinaka miss_hit opou vriskontai ola ta apotelesmata
			if(pointer1[k].index==check_index)
			{
				if(pointer1[k].valid==0)
				{
					*miss_hit="Miss";
					*typos_miss="Compulsory";
					miss++;
				}
			}
			else if(pointer1[k].tag==check_tag)
			{
				if(block_offset>0)
				{
					if(pointer1[k].block_offset==1)
					{
						*miss_hit="Hit";
						hit++;
					}
					else
					{
						*miss_hit="Miss";
						*typos_miss="Capasity";
						miss++;
					}
				}
				else
				{
					*miss_hit="Hit";
					hit++;
				}
			}
			else
			{
				*miss_hit="Miss";
				*typos_miss="Conflict";
				miss++;
			}
		}
	}
	sinolikoi_kikloi=0;
	// an to action einai "w" kanei ta akolou8a
	if(pinakas[0]=='w'|| pinakas[0]=='r')
	{
		for(k=0;k<lexeis;k++)
		{
			if(pointer1[k].index==check_index)// an to index isoutai tote kanei tous parakatw elegxous
			{
				if(pointer2[k].valid==0)// an to valid=0 tote einai miss
				{
					*miss_hit="Miss";
					*typos_miss="Compulsory";
					miss++;
					pointer1[k].tag=check_tag;
					pointer1[k].block_offset=check_blockoffset;
					pointer1[k].valid=1;
				}
					else if(pointer1[k].tag==check_tag)//valid=1 kai tag einai idio
					{
					if(block_offset>0)// an iparxei to block_offset
					{
						if(pointer1[k].block_offset==check_blockoffset) // an to blockoffset idio tote einai hit
						{
							*miss_hit="Hit";
							hit++;
						}
						else//an to tag einai to idio alla oxi to blockoffset
						{
							*miss_hit="Miss";
							*typos_miss="Capasity";
							miss++;
							pointer1[k].tag=check_tag;
							pointer1[k].block_offset=check_blockoffset;
							pointer1[k].valid=1;
						}
					}
					else //to blockoffset den iparxei ara einai "Hit"
					{
						*miss_hit="Hit";
						hit++;
					}
				}
					else// an to tag einai diaforetiko tote einai "miss"
					{
						*miss_hit="Miss";
						*typos_miss="Conflict";
						miss++;
						pointer1[k].tag=check_tag;
						pointer1[k].block_offset=check_blockoffset;
						pointer1[k].valid=1;
					}
				}// kleisimo gia ton elegxo tou index
			
			}//kleisimo tou parsing tou arxeiou dedomenw(arxitektoniki.txt)
	//edw ekteloume tin poliki na einai write-through kai write allocate
	if(write_through==1 && write_allocate==1)
	{
		// an to apotelesma tou telikou pinaka miss_hit einai miss tote kanei tis kanei tis katalliles pra3eis
		//gia na ipologisei tous sinolikous kiklous
		if(*miss_hit=="Miss")
		{
			sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram+read_from_ram+write_to_cache;
		}
		else // an einai "Hit"
		{
			if(*miss_hit=="Hit")
			{
				sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram;
			}	
		}
	}//kleisimo gia write_through kai write_allocate
	else if((write_through==1) && (no_write_allocate==1))
	{
		if(*miss_hit=="Miss")
		{
			sinolikoi_kikloi=sinolikoi_kikloi+ write_to_cache +write_to_ram;
		}
		else
			sinolikoi_kikloi=sinolikoi_kikloi+write_to_ram;
		}//Kleisimo gia to write_through kai no_write_allocate
		else if (write_back==1 && write_allocate==1)
		{
			if (*miss_hit== "Miss")
				if(pointer1[check_index].dirty==1)
				{
					sinolikoi_kikloi =sinolikoi_kikloi+ write_to_cache + write_to_ram + read_from_ram;
				}
				else 
				{
					sinolikoi_kikloi = write_to_cache;
					pointer1[check_index].dirty = 1;
				}
		}//kleisimo gia to write_back kai write_allocate
		else if(write_back==1 && no_write_allocate==1)
		{
			if(*miss_hit=="Miss")
			{
				sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache+write_to_ram;
			}
			else 
			{
				sinolikoi_kikloi=sinolikoi_kikloi+write_to_cache;
				pointer1[check_index].dirty=1;
			}
		}//kleisimo gia to write_back kai no_write_allocate
	
	else
	{
		if(*miss_hit=="Miss")
		
			sinolikoi_kikloi=sinolikoi_kikloi+read_from_cache+read_from_ram;
		
		else
			sinolikoi_kikloi=sinolikoi_kikloi+read_from_cache;
		}
		}//kleisimo gia to action "w" kai "r"
	
	// an to action einai "f" arxikopoiei ola ta valid me 0 kai ta index menoun ta idia
	if(pinakas[0]=='f')
	{
		for(k=0;k<lexeis;k++)
		{
			pointer1[k].valid=0;
			pointer1[k].index=k;
		}
	}// kleisimo gia to action "f"
	printf("\n");
	printf("Tag = %d\n",check_tag);
	printf("Index = %d\n",check_index);
	printf("Block Offset = %d\n",check_blockoffset);
	
	}//kleisimo tou for()
	fprintf(header2,"\t%s",*miss_hit);
	fprintf(header2, "\n");
	printf("Oi epitixeis prospa8ies einai %d\n",hit);
	printf("Oi apotixeis prospa8ies einai %d\n", miss);
	}// kleisimo while() gia to diavasma tou arxeiou 
	}// kleisimo gia to if() tis n-way-associative
	
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
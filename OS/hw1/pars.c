
	#include<stdio.h>
	#include<string.h>

	int main()
	{
		FILE *ptr_file;
		int x;
		char buf[100];

		ptr_file =fopen("market.txt", "r");
		int i=1;
		if (!ptr_file)
			return 1;
		
		char startDay[100];
		sprintf(startDay, "#START DAY %d#\n", i);
		
		char a[20];
		char b[20];
		char c[20];
		
		int milk=0;
		int biscuit=0;
		int chips=0;
		int coke=0;

		
		while (fgets(buf,100,ptr_file)!=NULL)
		{
			sscanf(buf, "%s" "%s" "%s",a,b,c);
			if(0==strcmp(a,"#START"))
        		{
        				printf("Day #%c\n",c[0]);
        				milk=0;
						biscuit=0;
						chips=0;
						coke=0;   
						 				        			
				}else if(strstr(buf, "MILK") != NULL)
				{	
					milk++;
					
				}else if(strstr(buf, "BISCUIT") != NULL)
				{	
					biscuit++;
					
				}else if(strstr(buf, "CHIPS") != NULL)
				{	
					chips++;
					
				}else if(strstr(buf, "COKE") != NULL)
				{	
					coke++;
					
				}else if(0==strcmp(a,"#END"))
				{
					printf("%d milk, %d biscuit, %d chips, %d coke\n",milk,biscuit,chips,coke);
				}
		}
        	
        		

		fclose(ptr_file);

		return  0;
	}

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char *argv[])
{
	DIR *dir;
	struct dirent *dp;
	char path[512] = "";
	char ex_name_list[128][128];
	char ex_name_folder[128][128];
	char ex_name[128] = "";
	char target_folder[128] = "";
	char current_directory[128][128];
	char file_path[128][128];
	int i = -1;
	int j,check,count,k;
	count = 0;
	
	if(argc<=1){
		strcpy(path,".");
	}
	else{
		strcpy(path,argv[1]);
	}
	if((dir=opendir(path))==NULL){
		perror("opendir");
		exit(-1);
	}
	for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)){
		check = 1;
		if(strstr(dp->d_name,".") != NULL){
			strcpy(ex_name,strstr(dp->d_name,"."));
			for(j=0;j<=count;j++)
			{
				if(strcmp(ex_name_list[j],ex_name) == 0)
				{
					check = 0;
				}
			else if((strcmp(ex_name,".") == 0) || (strcmp(ex_name,"..") == 0) || (strcmp(ex_name,".DS_Store") == 0)) //"."と".."と"DS_store"は除く
			{
				check = 0;
			}

		}
		if(check == 1)
		{
			i++;
			strcpy(ex_name_list[i],ex_name);
		}
		count++;
	}
}
closedir(dir);


for(j=0;ex_name_list[j][0] != '\0';j++)
{
	printf("%s",ex_name_list[j]);
	strcpy(target_folder,ex_name_list[j]);
	for(k=0;ex_name_list[j][k] != '\0';k++)
	{
		ex_name_list[j][k] = ex_name_list[j][k+1];
	}
	strcpy(ex_name_folder[j],strcat(ex_name_list[j],"のフォルダ"));
	strcpy(current_directory[j],path);
	strcat(current_directory[j],"/");
	strcat(current_directory[j],ex_name_folder[j]);
	mkdir(current_directory[j],0755);
	printf("　%sを作成しました\n",ex_name_folder[j]);

	if((dir=opendir(path))==NULL){
		perror("opendir");
		exit(-1);
	}

	for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)){
		if(strstr(dp->d_name,".") != NULL){
			strcpy(ex_name,strstr(dp->d_name,"."));
			if(strcmp(target_folder,ex_name) == 0)
			{
				strcat(current_directory[j],"/");
				strcat(current_directory[j],dp->d_name);
				strcpy(file_path[j],path);
				strcat(file_path[j],"/");
				strcat(file_path[j],dp->d_name);
				if(strcmp(dp->d_name,"make_d2.c") != 0){
					if( rename( file_path[j], current_directory[j] ) != 0 ){
						printf("移動に失敗しました\n");
					}
					else{
						printf("%sを%sに移動しました\n",dp->d_name,ex_name_folder[j]);
					}
				}
			}
		}
	}
	closedir(dir);
}
return 0;
}
#include<stdio.h>
#include<string.h>
struct admin_db{
    char name[50],pwd[33];
}admin;

struct user_db{
    int id;
    char name[50],pwd[33],email[50];
}user[100];

struct exams{
    char name[50];
    int num_ques,exam_id,total_marks;
    
    struct questions{
        char ques[200],opt1[30],opt2[30],opt3[30],opt4[30];
        int crt_ans;
    }question[50];
    
}exam[100];

struct test{
    int user_id,exam_id,test_id,opt[50],marks;
}test[100];

void taketest(int exam_id,int user_id,int id){
    int i;
    test[id].test_id=id;
    test[id].marks=0;
    for(i=0;i<exam[exam_id].num_ques;i++){
        printf("%d. %s\n",i+1,exam[exam_id].question[i].ques);
        printf("1. %s\n",exam[exam_id].question[i].opt1);
        printf("2. %s\n",exam[exam_id].question[i].opt2);
        printf("3. %s\n",exam[exam_id].question[i].opt3);
        printf("4. %s\n",exam[exam_id].question[i].opt4);
        scanf("%d",&test[id].opt[i]);
        if(test[id].opt[i]==exam[exam_id].question[i].crt_ans)
            test[id].marks++;    
    }
}
int main(){
    FILE *fp;
    int choice,num_users=0,num_exam=0,num_test=0,id,i,j,k,x,c=0;
    char cfm_pwd[33],username[50],password[33];
    
    strcpy(admin.name,"admin");
    strcpy(admin.pwd,"admin");
    
    while(1){
        printf("\n                                  ************** Online Quiz Application ***********                     \n");
        printf("\nSelect one from the below : \n");
        printf("1. user registration\n");
        printf("2. user login\n");
        printf("3. admin login\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                fp=fopen("user_data.txt","a+");
                x=num_users;
                printf("Enter the username: ");
                scanf("%s",user[num_users].name);
                
                do{
                    printf("Enter the password: ");
                    scanf("%s",user[num_users].pwd);
                    printf("Confirm the password: ");
                    scanf("%s",cfm_pwd);    
                }while(strcmp(cfm_pwd,user[num_users].pwd)!=0);
                printf("Enter the Gmail address: ");
                scanf("%s",user[num_users].email);
                char a[100];
                strcpy(a,user[num_users].email);
                for(j=0;j<strlen(a);j++)
                {
                    if(a[j]=='@')
                    {
                        for(k=j+1;k<strlen(a);k++)
                        {
                            if(a[k]=='@')
                            {
                            c=1;
                            break;
                            }
                            if(a[k]=='.')
                            {
                                num_users++;
                                c=1;
                                break;
                            }
                        }
                    }
                    if(c==1)
                       break;
                }
                if(x+1!=num_users)
                    printf("your Gmail is not in proper format\n");
                else{
                    printf("-------------registered successfully--------------\n");
                    fprintf(fp,"id: %d \n",num_users-1);
                    fprintf(fp,"username: %s \n",user[num_users-1].name);
					fprintf(fp,"password: %s \n",user[num_users-1].pwd);
					fprintf(fp,"email: %s \n",user[num_users-1].email);
                }
                fclose(fp);     
                break;
                
            case 2:
                    printf("Enter the username: ");
                    scanf("%s",username);
                    printf("Enter the password: ");
                    scanf("%s",password);
                    for(i=0;i<num_users;i++){
                        if(strcmp(username,user[i].name)==0){
                            if(strcmp(password,user[i].pwd)==0){
                                while(choice!=3){
                                id=i;
                                printf("1.Take Test\n");
                                printf("2.Results of previous exams\n");
                                printf("3.logout\n");
                                scanf("%d",&choice);
                                switch(choice){
                                    case 1:
                                        printf("The exams available are:\n");
                                        for(i=0;i<num_exam;i++){
                                            printf("%d. %s \n",i+1,exam[i].name);
                                        }
                                        printf("Select one from the above: ");
                                        scanf("%d",&choice);
                                        if(choice<=num_exam){
                                            taketest(choice-1,id,num_test);
                                            num_test+=1;
                                        }
                                        break;
                                    case 2:
                                        for(i=0;i<num_test;i++){
                                            if(test[i].user_id==id){
                                                printf("Exam Id: %d \n",test[i].exam_id);
                                                printf("Exam Name: %s \n",exam[test[i].exam_id].name);
                                                printf("Marks: %d \t Total Marks: %d \n",test[i].marks,exam[test[i].exam_id].total_marks);
                                            }
                                        }
                                        break;
                                    case 3:
                                    printf("---------------------Logged Out---------------------\n");
                                        break;
                                    default:
                                        printf("Please select only from the above\n");
                                }    
                            }
                        }else
                               printf("Incorrect password");
                    }           
                    else
                        printf("Incorrect username\n");
                }
                break;
                
            case 3:
                printf("Enter the username: ");
                scanf("%s",username);
                printf("Enter the password: ");
                scanf("%s",password);
                if(strcmp(username,admin.name)==0){
                    if(strcmp(password,admin.pwd)==0){
                        while(choice!=5)
                        {
                        printf("1. create Exam\n");
                        printf("2. view marks of all for each test \n");
                        printf("3. list marks in sorted order \n");
                        printf("4. search using candidiate name \n");
                        printf("5. Logout\n");
                        scanf("%d",&choice);
                        switch(choice){
                            case 1:
                                fp=fopen("exam.txt","a+");
                                fprintf(fp,"id: %d \n",num_exam);
                                printf("Enter the exam name: ");
                                scanf("%s",exam[num_exam].name);
                                fprintf(fp,"name: %s \n",exam[num_exam].name);
                                printf("Enter the number of questions: ");
                                scanf("%d",&exam[num_exam].num_ques);
                                fprintf(fp,"num_of_questions: %d \n",exam[num_exam].num_ques);
                                for(i=0;i<exam[num_exam].num_ques;i++){
                                    fprintf(fp,"%d. ",i+1);
                                    printf("Enter the questions: ");
                                    scanf("%s",exam[num_exam].question[i].ques);
                                    fprintf(fp,"%s \n",exam[num_exam].question[i].ques);
                                    printf("Enter the option 1: ");
                                    scanf("%s",exam[num_exam].question[i].opt1);
                                    fprintf(fp,"1. %s \n",exam[num_exam].question[i].opt1);
                                    printf("Enter the option 2: ");
                                    scanf("%s",exam[num_exam].question[i].opt2);
                                    fprintf(fp,"2. %s \n",exam[num_exam].question[i].opt2);
                                    printf("Enter the option 3: ");
                                    scanf("%s",exam[num_exam].question[i].opt3);
                                    fprintf(fp,"3. %s \n",exam[num_exam].question[i].opt3);
                                    printf("Enter the option 4: ");
                                    scanf("%s",exam[num_exam].question[i].opt4);
                                    fprintf(fp,"4. %s \n",exam[num_exam].question[i].opt4);
                                    printf("Enter the correct option: ");
                                    scanf("%d",&exam[num_exam].question[i].crt_ans);
                                    fprintf(fp,"Answer: %d \n",exam[num_exam].question[i].crt_ans);
                                }
                                exam[num_exam].total_marks=exam[num_exam].num_ques;
                                fprintf(fp,"total_marks: %d \n",exam[num_exam].total_marks);
                                exam[num_exam].exam_id=num_exam;
                                num_exam++;
                                fclose(fp);
                                break;
                            case 2:
                                printf("Enter the exam id: ");
                                scanf("%d",&id);
                                printf("Exam name: %s\n",exam[id].name);
                                for(i=0;i<num_test;i++)
                                {
                                    if(test[i].exam_id==id)
                                    {
                                        printf("userId: %d\n",test[i].user_id);
                                        printf("username: %s\n",user[test[i].user_id].name);
                                        printf("Marks obtained: %d\n",test[i].marks);
                                    }
                                }
                                printf("Total Marks: %d\n",exam[id].total_marks);
                                break;
                                
                            case 3:
                                printf("Enter the exam Id: ");
                                scanf("%d",&id);
                                int min=1000,prev_min=-1,c=0;
                                for(i=0;i<num_test;i++)
                                    if(test[i].exam_id==id)
                                        c+=1;
                                while(c--){
                                    for(i=0;i<num_test;i++){
                                        if(test[i].exam_id==id){
                                            if(test[i].marks<min && test[i].marks>prev_min)
                                                min=test[i].marks;    
                                        }
                                    }
                                    printf("%d\n",min);
                                    prev_min=min;
                                }        
                                break;
                            case 4:
                                printf("Enter the user name: ");
                                scanf("%s",username);
                                int count=0;
                                for(i=0;i<num_users;i++){
                                    if(strcmp(user[i].name,username)==0){
                                        id=user[i].id;
                                        break;
                                    }
                                }
                                for(i=0;i<num_test;i++){
                                    if(test[i].test_id==id){
                                        printf("userId: %d\n",test[i].exam_id);
                                        printf("username: %s\n",user[test[i].user_id].name);
                                        printf("Marks obtained: %d\n",test[i].marks);
                                        count++;
                                    }
                                }
                                printf("Number of tests attended: %d\n",count);
                                break;
                            case 5:
                                printf("---------------------Logged Out---------------------\n");
                        }
                      }
                    }
                }
                break;
            default:
                printf("Select only from the above\n");
        }
    }
}


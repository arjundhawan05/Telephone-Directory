/*********************
	HEADER FILES
************************/

#include<fstream>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<dos.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

using namespace std ;
/***********************
    SLEEP FUNCTION
***********************/
void sleep(unsigned int mseconds)
{
	 clock_t goal = mseconds + clock();
	 while (goal > clock());
}
/*********************
	     NODE
************************/

struct node
{
    char name[50];
    char mob[11];
    char email[50];
    node *left;
    node *right;

    node()
    {
        mob[0]='\0';
        email[0]='\0';
        left = NULL ;
        right =NULL ;
    }
};
/*********************
	CLASS TREE
************************/

class tree
{
    node *root;

public:
    tree()
    {
        root=NULL;
       /* root =new node ;
        root->left =NULL ;
        root->right =NULL ;
        strcpy(root->name ,"No Name");
        strcpy(root->email ,"No Email") ;*/
    }

    node* search_node(char *str) ;
    void insert_node(node *a) ;
    void delete_node(node a) ;
    node* return_root() ;
    void printInorder(node* ptr);
    void suggestion(char *a);
    char return_first(node *a)
    {
        return a->name[0];
    }

};
/*********************
	COMPARE FUNCTION
************************/

int compare( node *a ,node *b) ///returns 1 if a>b ; -1 if a<b ; 0 if a==b
{
    if(!strcmp(a->name ,b->name)&&b->mob[0]!='\0')
    {
        for(int i=0 ;i<10 ;i++)
        {
           if(a->mob[i]>b->mob[i])
            return 1 ;
           else if(a->mob[i]<b->mob[i])
            return -1 ;
        }
        return 0;
    }
    int i=0;
    for(  ;a->name[i]!='\0'&&b->name[i]!='\0' ;i++)
    {
        if(a->name[i] > b->name[i])
            return 1 ;
        else if(a->name[i] <b->name[i])
            return -1 ;
    }
    if(a->name[i]=='\0'&&b->name[i]=='\0')
        return 0;
    else if(a->name[i]=='\0')
        return -1 ;
    else
        return 1 ;

}

/*********************
	GET NODE
************************/

node* getnode( node *temp)
{
    cout<<"\tEnter the name =";
    cin.getline(temp->name ,50) ;
    cout<<"\tEnter the phone no =";
    char ch;
    int i;
    for( i=0 ;i<10 ;i++)
    {
        cin.get(ch);
        if(ch==' '||ch=='\n')
        {
            i--;
            continue ;
        }
        temp->mob[i] = ch;
    }
    temp->mob[i] = '\0' ;
    cout<<"\tEnter the email =";
    cin.get();
    cin.getline(temp->email ,50) ;
    return temp;
}
/*********************
	SHOW NODE
************************/

node *shownode( node *temp)
{
    cout<<"\tName ="<<temp->name;
    cout<<"\n\tMobile no.="<<temp->mob;
    cout<<"\n\tEmail ="<<temp->email ;
}
/*********************
	SEARCH NODE
************************/

node* tree::search_node(char *str)
{
    node *ptr =root ;
    node a ;
    strcpy(a.name ,str);
    if(root==NULL)
    {
      return root ;
    }

    while(ptr!=NULL)
    {
        int t = compare(ptr , &a) ;
        if(t==1)///ptr >a
        {
            ptr = ptr->left ;
        }
        else if (t==-1) ///ptr <a
        {
            ptr = ptr->right ;
        }
        else if(t==0)
        {
            return ptr ;
        }

    }

    return ptr ;
}
/*********************
	INSERT NODE IN BST
************************/


void tree::insert_node(node *temp)///input in this function
{
    node *ptr = root ;

    if(root==NULL)
    {
      root=temp ;
    }

    while(ptr!=NULL)
    {
        int t = compare(ptr , temp) ;
        if(t==1)///ptr >temp
        {
            if(ptr->left==NULL)
            {
                ptr->left =temp;
                return ;
            }

            ptr = ptr->left ;
        }
        else if (t==-1) ///ptr <temp
        {
            if(ptr->right==NULL)
            {
                ptr->right =temp;
                return ;
            }

            ptr = ptr->right ;
        }
        else if(t==0)
        {
            cout<<"Already Present, Please try again ";

        }

    }

}
/*********************
  PRINT NODES (SORTED)
************************/

void tree::printInorder(node* ptr)
{
     if (ptr == NULL)
          return;

     /* first recur on left child */
     printInorder(ptr->left);

     /* then print the data of node */
     cout<<"\n________________________________\n";
     shownode(ptr);

     /* now recur on right child */
     printInorder(ptr->right);
}
/*********************
	RETURN ROOT
************************/

node* tree::return_root()
{
   return root;
}
/**************************************
  HASH ARRAY AND BST ARRAY(GLOBAL)
***************************************/

node * hash_table[26];
tree bst[26];
/*********************
	HASH INSERT
************************/

void hash_insert(node *a)
{

    char ch= a->name[0] ;
    ch =tolower(ch);
    int key = (int)(ch -'a');
    key =key%26 ;
    bst[key].insert_node(a);
    if(hash_table[key]==NULL)
    {
       hash_table[key] =bst[key].return_root();
    }

}
/*********************
	HASH ALL OUT
************************/

void hash_allout()
{
    int i;
    for(i =0;i<26;i++)
    {
        node *root =bst[i].return_root();
        bst[i].printInorder(root);
    }

}
/***********************
 HASH OUT SINGLE LETTER
************************/

void hash_out(char ch)
{
    int key = (int)(ch -'a');
    key =key%26 ;
    node *root =bst[key].return_root();
    bst[key].printInorder(root);

}
/***********************
  AUTO SUGGEST FUNCTIONS
************************/

bool checkSimilarity(char *a, char *b)
{
    cout <<"\nComparing " << a << " with " << b <<" ";

    for (int k =0 ; k<10 ;k++ )
	{cout<<" .";sleep(150); }
	system("cls");

    for(int i=0; a[i]!='\0'; i++)
    {
            cout << "Comparing " << a[i] << " and " << b[i] <<" ";
            for (int k = 0 ; k<10 ;k++ )
	       {cout<<" .";sleep(150); }

            system("cls");

        if(a[i]!=b[i]) return false;
    }
    return true;
}

///AUTO SUUGESTION TRAVESAL

void traversal(char *word, node *temp, int i)
{
    if(temp==NULL) return;

    if(checkSimilarity(word, temp->name))
    {
        cout << temp->name << endl;
        //strcpy(arr[i],node->name);
        //i++;
    }
    traversal(word, temp->left, i);
    traversal(word, temp->right, i);
}

///SUGGESTING FUNCTION

void suggest(char *ch)
{
    char c=ch[0];
    node* temp = ::hash_table[int(c-'a')];

    //cout << "searching in hash table with index " << c-'a' << endl;

    if(temp==NULL) cout << "Null";

    traversal(ch, temp, 0);

    return;
}

/*********************
	NEW NODE
************************/

node *new_node()
{
    node *temp =new node ;
    return temp ;
}
///INTRO
void intro();
///INSERT FUNCTION
void insert_function();
///SEARCH FUNCTION
void search_function();
///DISPLAY FUNCTION
void dislay_finction() ;
/*********************
	MAIN FUNCTION
************************/

int main()
{
    tree a ;
    intro();
    for ( int n   ;     ;    )
  {
	system("cls") ;

	cout<<"\n\n\n\n\t\t";
	cout<<"\n\t\t\t\t\t            WELCOME       ";
	cout<<"\n\t\t\t\t\t              TO         ";
	cout<<"\n\t\t\t\t\t           DIRECTORY    \n";
	cout<<"\n\t\t\t\t\t                              \n";
	cout<<"\n\t\t\t\t\t    +++++++++++++++++++++++";
	cout<<"\n\t\t\t\t\t    +                     +";
	cout<<"\n\t\t\t\t\t    +      1.INSERT       +";
	cout<<"\n\t\t\t\t\t    +                     +";
	cout<<"\n\t\t\t\t\t    +      2.DELETE       +";
	cout<<"\n\t\t\t\t\t    +                     +";
	cout<<"\n\t\t\t\t\t    +      3.SEARCH       +";
	cout<<"\n\t\t\t\t\t    +                     +";
	cout<<"\n\t\t\t\t\t    +      4.DISPLAY      +";
	cout<<"\n\t\t\t\t\t    +                     +";
	cout<<"\n\t\t\t\t\t    +      5.EXIT         +";
	cout<<"\n\t\t\t\t\t    +                     +";
	cout<<"\n\t\t\t\t\t    +++++++++++++++++++++++";
	cout<<"\n\n\t\tPLease Enter your choice :  ";
	 cin>>n;
	switch(n)
	 {
	  case 1:insert_function();break;
	  case 2: ///delete function to be made

	      break;
	  case 3:cin.get();
	      search_function();

	      break;

	  case 4: dislay_finction() ;

	      break;

	  case 5:{
				 system("cls") ;
				 cout<<"\n\n\n\n\n\n";
				 cout<<"\n\t\t\t    !!! THANK YOU !!!\n ";
				 cout<<"\n\t\t\t    !!!   HAVE    !!! ";
				 cout<<"\n\t\t\t    !!!    A      !!! ";
				 cout<<"\n\t\t\t    !!!   GOOD    !!! ";
				 cout<<"\n\t\t\t    !!!   DAY     !!! ";
				 exit(0);
				}

	  default:{
				 system("cls") ;
				 sleep(750);
				 cout<<"\n\n" ;
             cout<<"\n\t\t\t                              \n";
	cout<<"\n\t\t\t     ________________________";
	cout<<"\n\t\t\t    |                        |";
	cout<<"\n\t\t\t    |    ___         ___     |";
	cout<<"\n\t\t\t    |   |___|       |___|    |";
	cout<<"\n\t\t\t    |                        |";
	cout<<"\n\t\t\t    |           |            |";
	cout<<"\n\t\t\t    |        ________        |";
	cout<<"\n\t\t\t    |       |        |       |";
	cout<<"\n\t\t\t    |________________________|";
	cout<<"\n\t\t\t                              ";
	cout<<"\n\t\t\t          WRONG CHOICE        ";
	cout<<"\n\t\t\t                              ";
				 sleep(1550);
				 system("cls") ;
				 }
	 }

  }

return 0;


}

/***********************
        INTRO
************************/
void intro()
 {
cout<<"\n";
cout<<"\n";
cout<<"\n";
cout<<"\n";
cout<<"\n\t        *********   **   ********   ******  *******  ********  ********  ********   ***    ***   ";
cout<<"\n\t        *********   **   ********   ******  *******  ********  ********  ********    **    **     ";
cout<<"\n\t        *      **   **   **    **   **      **          **     **    **  **    **     **  **        ";
cout<<"\n\t        *      **   **   ********   ******  **          **     **    **  ********      ****       ";
cout<<"\n\t        *      **   **   ******     **      **          **     **    **  ******         **          ";
cout<<"\n\t        *********   **   **   **    ******  *******     **     ********  **   **        **       ";
cout<<"\n\t        *********   **   **   ***   ******  *******     **     ********  **   ***       **        ";
  cout<<"\n\n\n\n\t\t\t\t              TELEPHONE DIRECTORY \t\t   \n\n\n";
  cout<<"\n\t\t\t\t\t   Press any key to continue " ;
  getch();
  system("cls") ;
cout<<"\n";
cout<<"\n";
cout<<"\n";
cout<<"\n\t        *********   **   ********   ******  *******  ********  ********  ********   ***    ***   ";
cout<<"\n\t        *********   **   ********   ******  *******  ********  ********  ********    **    **     ";
cout<<"\n\t        *      **   **   **    **   **      **          **     **    **  **    **     **  **        ";
cout<<"\n\t        *      **   **   ********   ******  **          **     **    **  ********      ****       ";
cout<<"\n\t        *      **   **   ******     **      **          **     **    **  ******         **          ";
cout<<"\n\t        *********   **   **   **    ******  *******     **     ********  **   **        **       ";
cout<<"\n\t        *********   **   **   ***   ******  *******     **     ********  **   ***       **        ";
  cout<<"\n\n\n\n\t\t\t\t              TELEPHONE DIRECTORY \t\t   \n\n\n";
  cout<<"\n\n\t\t    "  ;
  for (int k = 0 ; k<39 ;k++ )
	{cout<<" "<<char(219);sleep(150); }

  system("cls") ;
 }

/***********************
      INSERT FUNCTION
************************/
void insert_function()
{
  system("cls");
  int x ;
  cout<<"\n\t\tHOW MANY ENTRIES DO YOU WANT TO MAKE = " ;
  cin>>x ;
  cin.get() ;
  int i=1 ;
  while(i<=x)
  {
      cout<<"\n\tEntry "<<i<<"  \n";
      node *a=new_node();
      a = getnode(a) ;
      hash_insert(a) ;

      getch();
      system("cls");
      i++ ;
  }
     getch();
     system("cls");
     cout<<"Returning";
     for (int k = 0 ; k<10 ;k++ )
	 {cout<<" .";sleep(150); }

	 system("cls");
}
/***********************
      SEARCH FUNCTION
************************/
void search_function()
{
    system("cls");
    char str[50];
    cout<<"\n\t\tPLEASE ENTER THE NAME YOU WANT TO SEARCH = " ;
    cin.getline(str ,50) ;
    int key = (str[0] -'a')%26;
    node *a =bst[key].search_node(str);
    if(a==NULL)
        {cout<<"\n\tTHE ENTRY DOIES OT EXIST!!!";
         return ;
        }
   shownode(a);
   getch();
   system("cls");
   cout<<"Returning";
   for (int k = 0 ; k<10 ;k++ )
	{cout<<" .";sleep(150); }
	system("cls");

}
/***********************
    DISPLAY FUNCTION
************************/
void dislay_finction()
{
 system("cls");
 int x;

 for (  ;   ;  )
 {

 cout<<"\n";
 cout<<"\n\t\tDISPAY MENU " ;
 cout<<"\n\t\t1.SUGGESTIONS " ;
 cout<<"\n\t\t2.DISPLAY ALL RECORDS " ;
 cout<<"\n\t\t3.DISPLAY RECORDS STARTING WITH (character) " ;
 cout<<"\n\t\t4.EXIT " ;

 cin>>x ;

   switch(x)
   {
   case 1:  cout<<"\n\t\tEnter the word for suggestion =";
            char str[20];
            cin.get() ;
            cin.getline(str ,20) ;
            suggest(str) ;
            break ;

   case 2:  hash_allout();
            break ;

   case 3 : char ch;
            cout<<"\n\t\tEnter the alphabet of which records you want = " ;cin>>ch;
            hash_out(ch);
            break ;

   case 4 : return ;


   }
   getch() ;
   system("cls");
 }
}

#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<graphics.h>
class product{ int pno;
char name[50];
float price,qty,tax,dis;
public:
void create_product()
{ gotoxy(35,10);
textcolor(RED);
cputs("\n product no.->");
cin>>pno;
gotoxy(35,12);
cputs("\n\n product name ");
gets(name);
gotoxy(35,14);
cputs("\n product price ");
cin>>price;
gotoxy(35,16);
cputs(" discount on product ");
cin>>dis;
}
void show_product()
{ gotoxy(35,10);
textcolor(GREEN);
cputs("\n the product no. is ")<<pno;
gotoxy(35,12);
cputs("\n the product name is->");
puts(name);
gotoxy(35,14);
cout<<"the price of product is:"<<price;
gotoxy(35,16);
cout<<"\n discount"<<dis;
}
int retpno()
{ return pno;}
float retprice()
{return price;}
char*retname()
{ return name;}
int retdis()
{ return dis;}
};
fstream fp;
product pr;
void write_product()
{ fp.open("shop.dat",ios::out|ios::app);
pr.create_product();
fp.write((char*)&pr,sizeof(product));
fp.close();
cout<<"\n\n the product has been created";
getch();
}
void display_all()
{clrscr();
cout<<"\n\n\n\t display all record !!! \n\n";
fp.open("shop.dat",ios::in);
while(fp.read((char*)&pr,sizeof(product)))
{
pr.show_product();
cout<<"\n\n==================================\n";
getch();
}
fp.close();
getch();
}
void display_sp(int n)
{
int flag=0;
fp.open("shop.dat",ios::in);
while(fp.read((char*)&pr,sizeof(product)))
{
if(pr.retpno()==n)
{
clrscr();
pr.show_product();
flag=1;
}
}
fp.close();
if(flag==0)
cout<<"\n\n record not exist";
getch();
}
void modify_product()
{ int no,found=0;
clrscr();
cout<<"\n\n\t to modify";
cout<<"\n\n\t please enter the product no of the product";
cin>>no;
fp.open("shop.dat",ios::in|ios::out);
while(fp.read((char*)&pr,sizeof(product))&&found==0)
{
if(pr.retpno()==no)
{
pr.show_product();
cout<<"\n please enter new details of product"<<endl;
pr.create_product();
int pos=-1*sizeof(pr);
fp.seekp(pos,ios::cur);
fp.write((char*)&pr,sizeof(product));
cout<<"\n\n\t record updated";
found=1;
}
}
fp.close();
if(found==0)
cout<<"\n\n record not found";
getch();
}
void delete_product()
{int no;
clrscr(); 
cout<<"\n\n\n\tDelete record" ;
cout<<"\n\nPlease enter the product no. of the product you want to delete" ;
cin>>no; 
fp.open("shop.dat",ios::in|ios::out);
fstream fp2;
fp2.open("temp.dat",ios::out);
fp.seekg(0,ios::beg);
while(fp.read((char*)&pr,sizeof(product)))
{ 
if(pr.retpno()!=no)
{ fp2.write((char*)&pr,sizeof(product)); 
} 
} 
fp2.close(); 
fp.close(); 
remove("shop.dat");
rename("temp.dat","shop.dat"); 
cout<<"\n\nRecord deleted.."; 
getch(); 
} 

void menu() 
{ 
clrscr(); 
fp.open("shop.dat",ios::in);
if(!fp) 
{cout<<"ERROR!! FILE COULD NOT BE OPENED\n\n\n Go to admin menu to create file" ;
cout<<"\n\n\nThe program is closing--" ;
getch();
exit(0);
}
cout<<" \n\n\tPRODUCT MENU\N\N" ;
cout<<"===================================================================\n" ;
cout<<"P.NO. \t\tNAME\t\tPRICE\n" ;
cout<<"===================================================================\n";
while(fp.read((char*)&pr,sizeof(product)))
{cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
}
fp.close();
}
void place_order()
{int order_arr[50], quan[50],c=0;
float amt,damt,total=0;
char ch='Y';
menu(); 
cout<<"\n======================";
cout<<"\n PLACE YOUR ORDER" ;
cout<<"\n======================";
do{ 
cout<<"\n\nEnter the product no. o f the product:" ;
cin>>order_arr[c];
cout<<"\nQuantity in number:" ;
cin>>quan[c];
c++; 
cout<<"\nDo you want to order another  product?(y/n)"; 
cin>>ch;
} 
while(ch=='y'||ch=='Y') ;
cout<<"\n\nThank you for placing the order" ;
getch();
clrscr();
cout<<" ***************************INVOICE****************************\n";
cout<<"\n Pr.co. \tPr name\t Quantity \tPrice \tAmount \tAmount after disocut" ;
for(int x=0; x<=c;x++)
{
fp.open("shop.dat",ios::in);
fp.read((char*)&pr,sizeof(product));
while(!fp.eof())
{
if(pr.retpno()==order_arr[x])
 {
amt=pr.retprice() *quan[x];
damt=amt-(amt*pr.retdis()/100);
cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
total+=damt;
}
fp.read((char*)&pr,sizeof(product));
}
fp.close();
}
cout<<"\n\n\t\t\t\t\tTOTAL="<<total;
getch();
}

void intro()
{
clrscr();
gotoxy(31,11);
textcolor(YELLOW);
cputs("*****SUPER MARKET*****") ;
gotoxy(35,14);
textcolor(GREEN);
cputs("*****BILLING*****");
gotoxy(35,17);
textcolor(RED);
cputs("*****KARTIK NEGI*****");
getch();
}

void admin_menu()
{
clrscr();
char ch2;
textcolor(YELLOW);
cputs("\n\n ADMIN MENU");
gotoxy(35,10);
cputs("\n\n 1. CREATE NEW PRODUCT");
gotoxy(35,12);
cputs("\n\n 2.DISPLAY ALL PRODUCTS");
gotoxy(35,14);
cputs("\n\n 3.QUERY");
gotoxy(35,16);
cputs("\n\n 4.MODIFY PRODUCT");
gotoxy(35,18);
cputs("\n\n 5.DELETE PRODUCT");
gotoxy(35,20);
cputs("\n\n 6.VIEW PRODUCT MENU");
gotoxy(35,22);
cputs("\n\n 7.BACK TO MAIN MENU");
gotoxy(35,24);
cputs("\n\n please enter the choice(1-7)");
ch2=getche();
switch(ch2)
{

case '1': clrscr();
write_product();
break;
case '2': display_all();
break;
case '3': int num;
clrscr();
gotoxy(35,10);
textcolor(GREEN);
cputs("\n\n\tPRODUCT NO.");
cin>>num;
display_sp(num);
break;
case '4': modify_product();
break;
case '5': delete_product();
break;
case '6': menu();
getch();
case '7': break;
default:cout<<"\a";admin_menu();
}
}
void main()
{
char ch;
intro();
do
{
clrscr();
gotoxy(35,10);
textcolor(CYAN);
cputs("\n\n\tMAIN MENU");
gotoxy(35,12);
cputs("\n\n\t1->CUSTOMER");
gotoxy(35,14);
cputs("\n\n\t2->ADMINISTRATOR");
gotoxy(35,16);
cputs("\n\n\t3->EXIT");
gotoxy(35,18);
cputs("\n\n\tPLEASE SELECT ONE CHOICE(1-3)");
ch=getche();
switch(ch)
{
case '1': clrscr();
place_order();
getch();
break;
case '2': admin_menu();
break;
case '3':exit(0);
default :cout<<"\a";
}
} while(ch!='3');
}
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<string.h>
#include<fstream>
#include<iomanip>
#include<cctype>
#include "OPTAB.H"
#define LL long long
using namespace std;
string final[70][10];
/*First column contains line number
Second column contain Address 
Third column contain LABEL
Fourth column contain OPCODE
Fifth  column contain OPERAND
Sixth column contain format specification
Seventh column contain opcode
Eight column contain object_code
Ninth column contain index_address_flag  
Tenth column contain errors
*/
string SYMTAB[50][2],record[20];
/* This will convert Decimal to Hexadecimal string */
string convert_hex(LL n)
{
    char a;
    LL j;
    string ans;
    while(n!=0)
    {
        j=n&15;
        switch(j)
        {
            case 10:a='A';break;
            case 11:a='B';break;
            case 12:a='C';break;
            case 13:a='D';break;
            case 14:a='E';break;
            case 15:a='F';break;
            default: a= j+'0';break;
        }
        ans+=a;
        n=n>>4;
    }
    int size=ans.length();
    for(int i=0;i<size/2;i++)
    {
        char temp=ans[size-1-i];
        ans[size-i-1]=ans[i];
        ans[i]=temp;
    }
    return ans;
    
}
/*This will convert the Hexadecimal value to its corresponding decimal value*/
LL convert_int(string s)
{
    LL n=0,j,k=1;
    for(int i=s.length()-1;i>=0;i--)
    {
        char a=s[i];
        switch(a)
        {
            case 'A':j=10;break;
            case 'B':j=11;break;
            case 'C':j=12;break;
            case 'D':j=13;break;
            case 'E':j=14;break;
            case 'F':j=15;break;
            default: j=a- '0';break;
        }
        n+=j*k;k*=16;
    }
    return n;
}
// to convert an integer to a string...
string to_string(long long x)
{
       string ans="";
       long long a=0,b=x;
       while(b!=0)
       {
                  a=b%10;b=b/10;
                  ans=(char)(a+48)+ans;
       }
       return ans;
}
//used to give trailing zeros at the end of the string...
string give_zeros(int j,string s)
{
    string zeros,t;
    for(int i=0;i<(j-s.length());i++)
    zeros+="0";
    t=zeros+s;
    return t;
}
// to convert an string to a integer...
int to_int(string s)
{
    int k=0,x;
    for(int i=0;i<s.length();i++)
    {
        x=s[i]-'0';
        k*=10;
        k+=x;
    }
    return k;
}
int main()
{
/*This section is used to take input from the Input file from the users..*/
        string input;
        int length;
        ifstream file("Input.txt");
        if(file.is_open())
        {
            int index=0,flag=0;
            while(!file.eof())
            {
                file>>input;
                if(input[0]=='.')continue;
                if(flag==0)
                {
                if(input=="START")
                {
                    flag=-1;final[index][3]=input;
                    final[index][5]="#";
                    final[index][6]="#";
                }
                else if(input=="END")
                {
                    flag=-1;final[index][3]=input;
                    final[index][5]="#";
                    final[index][6]="#";
                }
                else if(input=="BYTE")
                {
                    flag=-1;final[index][3]=input;
                    final[index][5]="#";
                    final[index][6]="#";
                }
                else if(input=="WORD")
                {
                    flag=-1;final[index][3]=input;
                    final[index][5]="#";
                    final[index][6]="#";                
                }
                else if(input=="RESB")
                {
                    flag=-1;final[index][3]=input;
                    final[index][5]="#";
                    final[index][6]="#";
                }
                else if(input=="RESW")
                {
                    flag =-1;final[index][3]=input;
                    final[index][5]="#";
                    final[index][6]="#";
                }
                else if(input=="RSUB")
                {
                    final[index][3]=input;
                    final[index][0]=to_string(index+1);
                    final[index][5]=OPTAB[34][1];
                    final[index][6]=OPTAB[34][2];
                    index++;
                }
                else
            {
                for(int i=0;i<58;i++)     //58 is the length of the OPTAB defined in OPTAB.h
                {
                    if(OPTAB[i][0]==input)
                    {
                        flag=-1;
                        final[index][3]=input;
                        final[index][5]=OPTAB[i][1];
                        final[index][6]=OPTAB[i][2];
                        break;
                    }
                }
            }    
                }
                if(flag==0)
                {
                    final[index][2] = input;
                    continue;
                }
                if(flag==-1)
                {
                    flag=1;
                    continue;
                }
                if(flag==1)
                {
                    length=index+1;
                    final[index][0]=to_string(index+1);
                    if(input[input.length()-2]==',')final[index][8]="1";
                    else final[index][8]="0";
                    final[index][4]=input;index++;flag=0;
                    
                }
                
            }
            file.close();
        }
/*-------------------------- Starting Pass-1...Creating SYMTAB Table------------------------------*/
        int o=0,locctr,length_sym=0;
        string LOCCTR,pro_len;
        if(final[0][3]=="START")                  //Initializing location counter to address assign to START Label...
        {
            LOCCTR = final[0][4];
            final[0][1]=LOCCTR;
            SYMTAB[0][0]=final[0][2];
            SYMTAB[0][1]=LOCCTR;
            length_sym++;
            pro_len=LOCCTR;
            locctr=convert_int(LOCCTR);
        }
        else
         {
             o=-1;
            locctr=0;
            LOCCTR="0";
         }                       //Initializing location counter to 0 if start address is not given...
        while(final[++o][3]!="END" && o<length)
        {
            if(final[o][2]!="")
            {
                int q=-1,error_flag=0;          //0 error flag means there is no error
                while(SYMTAB[++q][0]!="")
                {
                    if(SYMTAB[q][0]==final[o][2])
                    {
                        error_flag=1;
                        break;
                    }
                }
                if(error_flag==1 )
                {
                    cout<<"Sry Syntax Error.\nInvalid LABEL used in line :- "<<final[o][0]<<endl;
                }
                else
                 {
                     SYMTAB[length_sym][0]=final[o][2];
                     SYMTAB[length_sym][1]=LOCCTR;
                     length_sym++;
                 }
            }
/*                        Increasing the location counter value....                                      */
            if (final[o][3]=="RESW")
            {
                final[o][1]=LOCCTR;
                locctr+=3*to_int(final[o][4]);
                LOCCTR=convert_hex(locctr);
            }
            else if (final[o][3]=="RESB")
            {
                final[o][1]=LOCCTR;
                locctr+=to_int(final[o][4]);
                LOCCTR=convert_hex(locctr);
            }
            else if(final[o][3]=="WORD")
            {
                final[o][1]=LOCCTR;
                locctr+=3;
                LOCCTR=convert_hex(locctr);
            }
            else if (final[o][3]=="BYTE")
            {
                int le;
                string temp=final[o][4];
                if(temp[0]=='X')
                {
                    le=(temp.length() - 3)/2;
                    final[o][7]=temp.substr(2,temp.length()-3);
                }
                else if(temp[0]=='C')
                {
                    int k=1;
                    le =temp.length() - 3;
                    while(k<temp.length()-2)
                    {k++;
                        final[o][7]+=convert_hex(int(temp[k]));
                    }
                }
                else cout<<"Undefined Symbol in Line- "<<final[o][0]<<endl;
                locctr+=le;
                final[o][1]=LOCCTR;
                LOCCTR=convert_hex(locctr);
            }
            else
            { 
                final[o][1]=LOCCTR;
                locctr+=to_int(final[o][5]);
                LOCCTR=convert_hex(locctr);
            }
        }
        SYMTAB[length_sym][0]="END";
        LOCCTR=convert_hex(locctr);
        final[o][1]=LOCCTR;
        SYMTAB[length_sym][1]=LOCCTR;
        length_sym++;
        pro_len=convert_hex(locctr-convert_int(pro_len));

/*                Increasing the location counter value ends....                         */
/*<---------------------------------------Starting the Pass -2 ----------------------->*/
        
        string temp,zeros;o=0;
        /*......................................Writing the header record.......................*/
        if(final[0][3]=="START")                
        {
            temp="H";
            temp+=final[0][2];
            for(int i=0;i<(6-final[0][2].length());i++)temp+=" ";
            for(int i=0;i<(6-final[0][4].length());i++)zeros+="0";
            temp+=zeros+final[0][4]+"";zeros="";
            for(int i=0;i<(6-pro_len.length());i++)zeros+="0";
            temp+=zeros+pro_len; 
            record[0]=temp;
        }
        else
         {
             o=-1;
             temp="H      ";                                    //Writing the header record...
             for(int i=0;i<6;i++)zeros+="0";
             temp+=zeros;zeros="";
             for(int i=0;i<(6-pro_len.length());i++)zeros+="0";
             temp+=zeros+pro_len;
             record[0]=temp;
         } 
         temp="";
  /*..................Generating the object code...............*/   
         
         while(final[++o][3]!="END" && o<length)
         {
             int flag=0;
             for(int i=0;i<58;i++)
                 if(OPTAB[i][0]==final[o][3])
                 flag=1;
             if(flag)
             {
                 if(final[o][4]!="")
                 {
                     int error_flag=1,index_flag=0;
                     if(final[o][8]=="1")
                     {
                         temp=final[o][4].substr(0,final[o][4].length()-2);
                         index_flag=1;
                     }
                     else temp=final[o][4];
                     
                     for(int j=0;j<length_sym;j++)
                     if(SYMTAB[j][0]==temp)
                     {
                         if(index_flag==0)
                         {
                             final[o][7]=final[o][6]+SYMTAB[j][1];
                         }
                     else final[o][7]=final[o][6]+convert_hex(convert_int(SYMTAB[j][1])+4096*8); //Taking consideration of the indexed mode of addressing....
                     error_flag=0;break;
                     }
                     if(error_flag)
                     {
                         final[o][7]=final[o][6]+"00*";
                         cout<<"Invalid Operand in Line "<<final[o][0]<<endl;
                     }
                 }
                 else final[o][7]=final[o][6]+"0000";
                 
             }
             else if(final[o][3]=="WORD")
             {
                 final[o][7]=give_zeros(6,convert_hex(to_int(final[o][4])));
             }
             
         }
  /*Pass-2 ends here..what we have done is generated object code & stored it in final string array...*/
  /*Starting writing the text record in the record array....*/
         o=0;
        if(final[0][3]!="START")o=-1;
        temp="T";
        temp+=give_zeros(6,final[0][1]);
        temp+="  ";
        int cnt=0,j=0;
        int flag=0;
        while(final[++o][3]!="" && o<length)
        {
            
            if(cnt<=30 && final[o][3]!="RESW" && final[o][3]!="RESB")
            {
                if(flag)
                {
                    temp="T";if(final[o-1][3]=="RESW" || final[o-1][3]=="RESB")temp+=give_zeros(6,final[o][1]);
                    else temp+=give_zeros(6,final[o-1][1]);
                    temp +="  ";flag=0;temp+=final[o-1][7];
                    cnt+=(final[o-1][7].length())/2;
                }
                cnt+=(final[o][7].length())/2;
                if(cnt<=30)temp+=final[o][7];
            }
            else if(flag==0)
            {
               if(cnt>30)
                cnt-=final[o-1][7].length()/2;
                o-=1;
                string ss=give_zeros(2,convert_hex(cnt));
                temp[7]=ss[0];
                temp[8]=ss[1];
                cnt=0;flag=1;
                record[++j]=temp;
                temp="";
            }
        }
        if(cnt<=30){
        string ss=give_zeros(2,convert_hex(cnt));
        temp[7]=ss[0];
        temp[8]=ss[1];
        }    
        record[++j]=temp;
        temp="";
        record[++j]="E";                            //Writing the END Redord....
        temp=final[o-1][4];
        for(int i=0;i<length_sym;i++)
        if(temp==SYMTAB[i][0])temp=SYMTAB[i][1];
        record[j]+=give_zeros(6,temp);
/*....................Writing Records and Program in files.....................*/
        
        ofstream output;
        output.open("Record.txt");
        if(output.is_open())
        {
            for(int i=0;record[i]!="";i++)
            {
                output<<record[i]<<endl;
            }
        }
        output.close();
        output.open("Overall_program.txt");
        if(output.is_open())
        {
            for(int i=0;i<length;i++)
        {for(int j=0;j<10;j++)
        {output<<setfill(' ')<<setw(9)<<final[i][j];}
        output<<endl;}
            
        }
        output.close();
        output.open("SYMTAB.txt");
        {
            if(output.is_open())
            {
                for(int i=0;i<length_sym;i++)
        {for(int j=0;j<2;j++)
        {output<<setfill(' ')<<setw(6)<<SYMTAB[i][j];}
        output<<endl;}
                
            }
        }
        output.close();
/*..............Writing the program on the console...................*/
    cout<<"This is the overall program with its generated object code\n\n"<<endl;
        for(int i=0;i<length;i++)
        {for(int j=0;j<8;j++)
        {cout<<setfill(' ')<<setw(8)<<final[i][j];}
        cout<<endl;}
}




















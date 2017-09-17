/************************************************************************************
 * Program: Mine_sweeper
 * Author: Gabriel Cisneros
 * Date: 03/13/16
 * Description: Mine sweeper game
 * Input: rows, columns, mines.
 * Output: game board
 * *********************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

/************************************************************************************
 * Funtion:checkNum
 * Description: checks if input is a num.
 * Parameters: char a
 * Pre-conditions: a is a number
 * Post-conditions: bool determining true or false
 ***********************************************************************************/


bool checkNum(char a){
	int test = a;
	if(a> 48 && a<58)
		return true;
	else
		return false;
};

/************************************************************************************
 * Funtion: argCheck
 * Description: checks arguements
 * Parameters: int argC, char **argV, int &r, int &c, int &cc, int &m, int &mc
 * Pre-conditions: r, c, and m has to be numbers.
 * Post-conditions: program will work if valid inputs
 ***********************************************************************************/

void argCheck(int argC,char **argV,int &r,int &rc,int &c,int &cc,int &m,int &mc) {
	for(int i=1; i<argC; i+=2){
		if(strcmp("-r", argV[i]) == 0 && checkNum(*argV[i+1])==true){
			r = atoi(argV[i+1]);
			rc++;
		}
		else if(strcmp("-c", argV[i])==0 && checkNum(*argV[i+1])==true){
			c = atoi(argV[i+1]);
			cc++;
		}
		else if(strcmp("-m", argV[i])== 0 && checkNum(*argV[i+1])==true){
			m= atoi(argV[i+1]);
			mc++;
		}
		else{
			cout<<"Invalid input, please try again."<<endl;
			exit(1);
		};
	};
};

/************************************************************************************
 * Funtion: createBoard
 * Description: creates playing board
 * Parameters: int r, int c
 * Pre-conditions: r and c have to be greater than 0.
 * Post-conditions: 2d dynamic array made to represent board
 ***********************************************************************************/

int ** createBoard(int r, int c){
	int ** array = new int *[r];
	for(int i=0; i<r; i++){
		array[i] = new int[c];
	};
	return array;
};

/************************************************************************************
 * Funtion: addNULL
 * Description: add NULLs to board
 * Parameters: int **b, int r, int c
 * Pre-conditions: r and c have to be greater than 0
 * Post-conditions: Nulls added to board array
 ***********************************************************************************/

void addNULL(int **b,int r,int c){
	for(int i=0; i<r; i++) {
		for(int k=0; k<c; k++){
			b[i][k]=0;
		};
	};
};

/************************************************************************************
 * Funtion: addINT
 * Description: add representitive INTs to board
 * Parameters: int **b, int r, int c
 * Pre-conditions: r and c greater than 0.
 * Post-conditions: ints added to board
 ***********************************************************************************/

void addINT(int **b, int r, int c){
	for(int i=0; i<r; i++) {
		for(int k=0; k<c; k++){
			if(b[i][k]==0)
				b[i][k]=120;
		};
	};

};

/************************************************************************************
 * Funtion: ifFound
 * Description: if mine is found, add int indicator
 * Parameters: int j, int g, int i, int k, int **b
 * Pre-conditions: none
 * Post-conditions: ints added to cells by how many mines are around
 ***********************************************************************************/

void ifFound(int j, int g, int i, int k, int **b){
	if(b[j][g]==90)
		b[i][k] +=10;
};


/*
   void printB(int **b,int r,int c, int **cp, bool &hMine){//troubleshooting
   cout<<endl;
   cout<< "(R)\n";
   for (int i=0; i<r ; i++) {
   if(i+1<10)
   cout<<" "<<i;

   else{
   cout<<i;
   }
   for(int k=0; k<c; k++){
   if(cp[i][k]== 0){
   cout<<"|-!-";
   };
   if((b[i][k]>=10 && b[i][k]!=120 && b[i][k]!= 90)&& cp[i][k]!=0)
   cout<< "|-"<<b[i][k]/10<<"-";
   else if(b[i][k]==90 && cp[i][k]!=0) { //mine
   cout<<"|-*-";
   hMine=true;
   }	
   else if(b[i][k]== 120 && cp[i][k]!=0)
   cout<<"|-0-";
   else if(b[i][k]<8 && cp[i][k]!=0)
   cout<<"|-"<<b[i][k]<<"-";
   };
   cout<<"|";
   cout<<endl;
   };
   cout<<"    ";
   for(int j=0; j<c; j++){
   cout<<j;
   if(j!=c-1)
   cout<<"   ";
   };
   cout<<"  (C)";
   cout <<endl<<endl;	
   };
   */


/************************************************************************************
 * Funtion:printB
 * Description: prints board
 * Parameters: int **b, int r, int c, int **cp, bool &hMine
 * Pre-conditions: ints represent if opened or not
 * Post-conditions: prints board of progress 
 ***********************************************************************************/

void printB(int **b,int r,int c, int **cp, bool &hMine){
	cout<<endl;
	cout<< "(R)\n";
	for (int i=0; i<r ; i++) {
		if(i+1<10)
			cout<<" "<<i+1;

		else{
			cout<<i+1;
		}
		for(int k=0; k<c; k++){
			if(cp[i][k]== 0){
				cout<<"|-!-";
			};
			if((b[i][k]>=10 && b[i][k]!=12)&& cp[i][k]!=0)
				cout<< "|___";//cover shell
			else if(b[i][k]==9 && cp[i][k]!=0) { //mine
				cout<<"|-*-";
				hMine=true;
			}	
			else if(b[i][k]== 12 && cp[i][k]!=0)
				cout<<"|-0-";
			else if(b[i][k]<8 && cp[i][k]!=0)
				cout<<"|-"<<b[i][k]<<"-";
		};
		cout<<"|";
		cout<<endl;
	};
	cout<<"    ";
	for(int j=0; j<c; j++){
		cout<<j+1;
		if(j!=c-1)
			cout<<"   ";
	};
	cout<<"  (C)";
	cout <<endl<<endl;	
};

/************************************************************************************
 * Funtion: checkIn
 * Description: checks input by user
 * Parameters: int r, int c, int inR, int inC
 * Pre-conditions: ints are ints
 * Post-conditions: feedback on the input 
 ***********************************************************************************/

bool checkIn(int r,int c, int inR,int inC){
	if( inR >r-1 || inC > c-1)
		return true;
	else
		return false;
};


/************************************************************************************
 * Funtion: deleteB
 * Description: deletes board array
 * Parameters: int **b, int r, int c
 * Pre-conditions: 2d array
 * Post-conditions: 2d array deallicated
 ***********************************************************************************/

void deleteB(int **b,int r,int c){
	for (int i=0; i<r; i++){
		delete [] b[i];
	};
	delete [] b;
};

/************************************************************************************
 * Funtion: flag
 * Description: user flags on board
 * Parameters: int &r, int &c, int **b, int **cp, int & num
 * Pre-conditions: r and c in range
 * Post-conditions: flag on board
 ***********************************************************************************/

void flag(int &r, int &c, int **b, int** cp, int & numM){
	cout<<"Pick a row: ";
	cin >>r;
	cout<<"Pick a column: ";
	cin >> c;
	r--;//to line up with arrays
	c--;
	cp[r][c] = 0;
	numM--;	
};




/************************************************************************************
 * Funtion: checkCorners
 * Description: checks corners of board
 * Parameters: int i, int k, int r, int c, int **b
 * Pre-conditions: ints in range
 * Post-conditions: corners are checked for mines
 ***********************************************************************************/

void checkCorners(int i, int k, int r, int c, int** b){
	int j=i, g=k, y = i-0, x = (c-1)-k;
	if(y!=0){
		j--;
		ifFound(j,g,i,k,b);
	}
	else{
		j++;
		ifFound(j,g,i,k,b);
	};
	if(x!=0){
		g++;
		ifFound(j,g,i,k,b);
	}
	else{
		g--;
		ifFound(j,g,i,k,b);
	};
	if(i>j){
		j++;
		ifFound(j,g,i,k,b);
	}
	else{
		j--;
		ifFound(j,g,i,k,b);
	};

};

/************************************************************************************
 * Funtion: checkEdges
 * Description: checks edges of board
 * Parameters: int i, int k, int r, int c, int **b
 * Pre-conditions: ints in range
 * Post-conditions: edges of board checked for mines
 ***********************************************************************************/

void checkEdges(int i, int k, int r, int c, int**b){
	int j=i, g=k, y= (r-1)-i, x= (c-1)-k;
	if(x==0 || x== c-1){
		j++;
		ifFound(j,g,i,k,b);	
		j-=2;
		ifFound(j,g,i,k,b);
		if(x==0)// right edge
			g--;
		else
			g++;
		for(j; j<= i+1; j++)
			ifFound(j,g,i,k,b);
	}
	else if(y==0 || y== r-1){
		g++;
		ifFound(j,g,i,k,b);
		g-=2;
		ifFound(j,g,i,k,b);
		if(y==0){
			j--;
		}
		else{
			j++;
		}
		for(g; g<=k+1;g++)
			ifFound(j,g,i,k,b);

	}
};


/************************************************************************************
 * Funtion: numCells
 * Description: number cells based on how many mines are around
 * Parameters: int **b, int r, int c
 * Pre-conditions: ints in range
 * Post-conditions: cells numbered
 ***********************************************************************************/

void numCells(int **b, int r, int c){
	for(int i=0; i<r; i++){
		for(int k=0; k<c; k++){
			if(b[i][k]!= 90){
				if((k!=0 && i!=0) && (k!=c-1 && i!= r-1)){//avoid edge
					for(int j=i-1; j<=i+1;j++){
						for(int g=k-1;g<=k+1;g++){
							ifFound(j, g, i, k, b);
						};

					};
				}
				else if((k==c-1 && i==r-1)||(k==0 && i==0)||((k==0||i==0) && (k==c-1 || i==r-1)))
					checkCorners(i,k,r,c,b);
				else{
					checkEdges(i,k,r,c,b);	
				};
			}
		};
	};
};


/************************************************************************************
 * Funtion: addMines
 * Description: add mines at random
 * Parameters: int **b, int r, int c, int m
 * Pre-conditions: none
 * Post-conditions: mines added to board
 ***********************************************************************************/

void addMines(int **b, int r, int c, int m){
	int tr, tc;
	for(int i=0; i<m; i++){
		tr= rand() % r;
		tc=rand() % c;
		if(b[tr][tc]==0)
			b[tr][tc]=90;//change to 90
		else
			i--;
	};
	numCells(b,r,c);
	addINT(b,r,c);
};


/************************************************************************************
 * Funtion: pick
 * Description: user picks row and colm
 * Parameters: int &r, int &c, int **b, int **cp, int *turnc, int ar, int ac
 * Pre-conditions: none
 * Post-conditions: user picks a row and colm to be opened
 ***********************************************************************************/

void pick(int &r, int &c, int ** b, int ** cp, int & turnc,int ar,int ac){
	bool error = false;
	do{
		do{
			cout<<"Pick a row: ";
			cin >>r;
			cout<<"Pick a column: ";
			cin >> c;
			r--;
			c--;//to line up with arrays
			error = checkIn(ar,ac,r,c);
		}while(error);
		cout<<b[r][c]<<endl;
		if(b[r][c] == 120){
			turnc++;
			b[r][c]=b[r][c]/10;
			//recCall(ar,ac,r,c,b,turnc);
			error=false;
		}
		else if(b[r][c] == cp[r][c]){
			b[r][c]= b[r][c]/10;
			error = false;	
			turnc++;
		}
		else if(b[r][c] != cp[r][c]){
			cout<<endl;
			cout<<"Repeated value, pick another...\n";
			error = true;
		}
	}while(error);

};

/************************************************************************************
 * Funtion: userInput
 * Description: user picks an option
 * Parameters: int ar, int ac, int &r, int &c, int **b, int **cp, int &choice, int &turnc, int &numM
 * Pre-conditions: none
 * Post-conditions: user picks an option
 ***********************************************************************************/

void userInput(int ar, int ac,int & r, int & c, int** b, int **cp, int &choice, int &turnc, int & numM){
	cout<<"Number of flags: "<< numM<<endl;
	cout<<"(1) Open or (2) Flag: ";
	cin>>choice;
	if(choice ==1){
		pick(r,c,b,cp,turnc, ar, ac);	

	}
	else{
		if(numM>0){
			flag(r,c,b,cp,numM);
		}
		else{
			cout<<endl<<"Out of flags.\n";
			userInput(ar, ac,r, c, b, cp, choice, turnc, numM);

		}

	}
};


/************************************************************************************
 * Funtion: makeCp
 * Description: makes copy of board
 * Parameters: int **b, int r, int c
 * Pre-conditions: r and c greater than 0
 * Post-conditions: copy 2d dynamic array is made
 ***********************************************************************************/

int ** makeCp(int ** b,int r,int c){
	int ** array = new int *[r];
	for(int i=0; i<r; i++){
		array[i] = new int[c];
	};
	for(int i=0; i<r;i++){
		for(int k=0; k<c; k++)
			array[i][k]= b[i][k];
	};
	return array;
};

/************************************************************************************
 * Funtion: restart
 * Description: user inputs rows, colms, and mine for new game
 * Parameters: int &r, int &c, int &m
 * Pre-conditions: none
 * Post-conditions: new r,c,m
 ***********************************************************************************/

void restart(int &r,int &c, int &m){
	cout<<"rows: ";
	cin>> r;
	cout<<"columns: ";
	cin>> c;
	cout<<"mines: ";
	cin >>m;


};


int main(int argC, char ** argV){
	srand(time(NULL));
	bool hMine = false, again;
	int q,turnc=0,choice, ir,ic,r=0, rc=0, c=0, cc=0, m=0, mc=0;
	if(argC != 7){
		cout<<"Invalid input"<<endl;
		exit(1);
	}
	argCheck(argC, argV, r, rc, c, cc, m, mc);
	if(rc!=1 || cc!=1|| mc!= 1 || (m >=(r*c))){
		cout<<"Invalid input"<<endl;
		exit(1);
	}
	do{
		int ** b= createBoard(r, c);
		addNULL(b, r, c);
		addMines(b,r,c,m);
		int **cp = makeCp(b,r,c);
		int num = (r*c)-m, numM = m;
		printB(b, r, c, cp, hMine);
		do{
			userInput(r,c ,ir,ic, b, cp, choice, turnc, numM);
			printB(b, r, c, cp, hMine);
		}while(turnc != num && !hMine);
		printB(b, r, c, cp, hMine);

		if(hMine){
			cout<<"Hit a mine\n";
		}
		else
			cout<<"Won game.\n";
		deleteB(b, r,c);
		deleteB(cp,r,c);
		cout<<"Would you like to play again?\n"<<"1) yes, 2) no: ";
		cin>>q;
		if(q==1){
			restart(r,c,m);
			again = true;
		}	
		else
			again = false;

	}while(again == true);
	return 0;
}

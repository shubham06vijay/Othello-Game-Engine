#include<bits/stdc++.h>
using namespace std;

const int MAX = 1000; 
const int MIN = -1000; 
//int a[10][10];
typedef struct v_node{
	int x;
	int y;
	vector<int> length;
	vector<int> dirToFlip;
}vNode;

int isValid(int a,int b);
int findMove(int a[][8],int player, vector<vNode> &v);
int isValidMove(int a[][8],int player,int i,int j);
void flipBoard(vNode p, int tempBoard[][8],int player);
int getScoreOfBoard(int temp[][8]);
void print(int a[][8]);
int deleteV(vector<vNode> &v);
void printV(vector<vNode> &v);

void flipBoard(vNode p, int a[][8],int player)
{
//	cout << "Flipping node: " << p.x << " " << p.y << endl;
	a[p.x][p.y]=player;
	int i=p.x,j=p.y,k,l,m;
	for(m=0;m<p.dirToFlip.size();m++)
	{
//		cout << "Direction to flip: " << p.dirToFlip[m] << endl;
		if(p.dirToFlip[m]==1)
		{
			a[i-1][j-1]=player;
			for(k=i-2,l=j-2;isValid(k,l);k--,l--)
			{				
				if(a[k][l]==player)
				{												
					break;
				}
				a[k][l]=player;
			}
		}
		else if(p.dirToFlip[m]==2)
		{
			a[i-1][j]=player;
			for(k=i-2;k>=0 && a[k][j]!=-1;k--)
			{
				if(a[k][j]==player)
				{													
					break;
				}
				a[k][j]=player;
			}
		}
		else if(p.dirToFlip[m]==3)
		{
			a[i-1][j+1]=player;
			for(k=i-2,l=j+2;isValid(k,l);k--,l++)
			{
				if(a[k][l]==player)
				{												
					break;
				}
				a[k][l]=player;
			}
		}
		else if(p.dirToFlip[m]==4)
		{
			a[i][j-1]=player;
			for(k=j-2;k>=0;k--)
			{
				if(a[i][k]==player)
				{												
					break;
				}
				a[i][k]=player;
			}
		}
		else if(p.dirToFlip[m]==6)
		{
			a[i][j+1]=player;
			for(k=j+2;k<8;k++)
			{
				if(a[i][k]==player)
				{												
					break;
				}
				a[i][k]=player;
			}
		}
		else if(p.dirToFlip[m]==7)
		{
			a[i+1][j-1]=player;
			for(k=i+2,l=j-2;isValid(k,l);k++,l--)
			{
				if(a[k][l]==player)
				{												
					break;
				}
				a[k][l]=player;
			}
		}
		else if(p.dirToFlip[m]==8)
		{
			a[i+1][j]=player;
			for(k=i+2;k<8 && a[k][j]!=-1;k++)
			{						
				if(a[k][j]==player)
				{													
					break;
				}
				a[k][j]=player;
			}
		}
		else if(p.dirToFlip[m]==9)
		{
			a[i+1][j+1]=player;
			for(k=i+2,l=j+2;isValid(k,l);k++,l--)
			{
				if(a[k][l]==player)
				{																			
					break;
				}
				a[k][l]=player;
			}
		}
	}
}
int getScoreOfBoard(int temp[][8])
{
//	print(temp);
	int bScore=0;
	int wScore=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(temp[i][j]==0)
			{
				bScore++;
			}
			else if(temp[i][j]==1)
			{
				wScore++;
			}
			if(i%8==0 && j%8==0)
			{
				if(temp[i][j]==0)
				{
					bScore+=10;
				}
				else if(temp[i][j]==1)
				{
					wScore+=10;
				}
			}
		}
	}
	return bScore-wScore;
}
int minimax(int tempBoard[][8],int depth, int maximizingPlayer, int alpha, int beta,vNode p,int player) 
{
	flipBoard(p,tempBoard,player);
//	print(tempBoard);
    if (depth == 5) 
        return getScoreOfBoard(tempBoard); 
  	
    if (maximizingPlayer) 
    {
//    	cout << "MAXIMIZING PLAYER" << endl;
        int best = MIN; 
        
        vector<vNode> temp;		
		findMove(tempBoard,1-player,temp);		
//		printV(temp);
        for (int i = 0; i < temp.size(); i++) 
        {
        	int tempBoard1[8][8];
			copy(&tempBoard[0][0], &tempBoard[0][0]+64,&tempBoard1[0][0]);
			int val;
			val = minimax(tempBoard1,depth+1,false,alpha,beta,temp[i],1-player);
				
//			cout << "val is: " << val << endl;
            best = max(best, val); 
            alpha = max(alpha, best); 
  
            if (beta <= alpha)
                break; 
        } 
        return best; 
    } 
    else
    { 
        int best = MAX;
//        cout << "MINIMIZING PLAYER" << endl;
        vector<vNode> temp;		
		findMove(tempBoard,1-player,temp);
//		printV(temp);
		int val;
        for (int i = 0; i < temp.size(); i++) 
        {
            int tempBoard1[8][8];            
			copy(&tempBoard[0][0], &tempBoard[0][0]+64,&tempBoard1[0][0]);
	
			int val = minimax(tempBoard1,depth+1,true,alpha,beta,temp[i],1-player);
			
//			cout << "val is: " << val << endl;
            best = min(best, val); 
            beta = min(beta, best); 
  
            if (beta <= alpha) 
                break; 
        } 
        return best; 
    } 
} 
void print(int a[][8])
{
	int i,j;
	cout << "\t";
	for(i=0;i<8;i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	for(i=0;i<8;i++)
	{
		cout << i << "\t";
		for(j=0;j<8;j++)
		{			
			if(a[i][j]==-1)
			{
				cout << "_" << "\t";
			}
			else if(a[i][j]==0){
				cout << "B" << "\t";
			}			
			else{
				cout << "W" << "\t";
			}
		}
		cout << endl;
	}
	cout << endl;
}
void printV(vector<vNode> &v)
{
	int i;
	for(i=0;i<v.size();i++)
	{
		cout << v[i].x <<" " << v[i].y;
		cout << endl; 
	}
	cout << "***************************\n";
}
int isValid(int a,int b)
{
	if(a<8 && b<8 && a>=0 && b>=0)
	{
		return 1;
	}
	else return 0;
}
int findMove(int a[][8],int player, vector<vNode> &v)
{
	int i,j,k,l;
	int count=0,flag=0;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			flag=0;
			if(a[i][j]==-1)
			{
				vNode temp;
				temp.x=i;
				temp.y=j;
				if(isValid(i+1,j) && a[i+1][j]==(1-player))
				{
					for(k=i+2;k<8 && a[k][j]!=-1;k++)
					{						
						if(a[k][j]==player)
						{	
							flag=1;
							count++;						
							temp.length.push_back(k-i-1);
							temp.dirToFlip.push_back(8);							
							break;
						}
					}
				}
				if(isValid(i-1,j) && a[i-1][j]==(1-player))
				{
					for(k=i-2;k>=0 && a[k][j]!=-1;k--)
					{
						if(a[k][j]==player)
						{	
							flag=1;	
							count++;			
							temp.length.push_back(i-k-1);
							temp.dirToFlip.push_back(2);							
							break;
						}
					}
				}
				if(isValid(i+1,j+1) && a[i+1][j+1]==(1-player))
				{
					for(k=i+2,l=j+2;isValid(k,l) &&a[k][l]!=-1;k++,l++)
					{
						if(a[k][l]==player)
						{
							flag=1;
							count++;
							temp.length.push_back(k-i-1);
							temp.dirToFlip.push_back(9);							
							break;
						}
					}
				}
				if(isValid(i+1,j-1) && a[i+1][j-1]==(1-player))
				{
					for(k=i+2,l=j-2;isValid(k,l) &&a[k][l]!=-1;k++,l--)
					{
						if(a[k][l]==player)
						{
							flag=1;
							count++;
							temp.length.push_back(k-i-1);
							temp.dirToFlip.push_back(7);							
							break;
						}
					}
				}
				if(isValid(i,j-1) && a[i][j-1]==(1-player))
				{
					for(k=j-2;k>=0 && a[i][k]!=-1;k--)
					{
						if(a[i][k]==player)
						{
							flag=1;
							count++;
							temp.length.push_back(j-k-1);
							temp.dirToFlip.push_back(4);							
							break;
						}
					}
				}
				if(isValid(i,j+1) && a[i][j+1]==(1-player))
				{
					for(k=j+2;k<8&&a[i][k]!=-1;k++)
					{
						if(a[i][k]==player)
						{
							flag=1;
							count++;
							temp.length.push_back(k-j-1);
							temp.dirToFlip.push_back(6);							
							break;
						}
					}
				}
				if(isValid(i-1,j-1) && a[i-1][j-1]==(1-player))
				{
					for(k=i-2,l=j-2;isValid(k,l) &&a[k][l]!=-1;k--,l--)
					{
						if(a[k][l]==player)
						{
							flag=1;
							count++;
							temp.length.push_back(i-k-1);
							temp.dirToFlip.push_back(1);							
							break;
						}
					}
				}
				if(isValid(i-1,j+1) && a[i-1][j+1]==(1-player))
				{
					for(k=i-2,l=j+2;isValid(k,l) &&a[k][l]!=-1;k--,l++)
					{
						if(a[k][l]==player)
						{
							flag=1;
							count++;
							temp.length.push_back(i-k-1);
							temp.dirToFlip.push_back(3);							
							break;
						}
					}
				}
				if(flag==1)
					v.push_back(temp);
			}
		}
	}
	return count;
}
int deleteV(vector<vNode> &v)
{
	v.clear();
	return 1;
}
int isValidMove(int a[][8],int player,int i,int j)
{
	int count=0,k,l;
	if(a[i][j]==-1)
	{
		if(isValid(i+1,j) && a[i+1][j]==(1-player))
		{
			for(k=i+2;k<8 && a[k][j]!=-1;k++)
			{						
				if(a[k][j]==player)
				{	
					count++;																				
					break;
				}
			}
		}
		if(isValid(i-1,j) && a[i-1][j]==(1-player))
		{
			for(k=i-2;k>=0 && a[k][j]!=-1;k--)
			{
				if(a[k][j]==player)
				{		
					count++;																	
					break;
				}
			}
		}
		if(isValid(i+1,j+1) && a[i+1][j+1]==(1-player))
		{
			for(k=i+2,l=j+2;isValid(k,l)&&a[k][l]!=-1;k++,l++)
			{
				if(a[k][l]==player)
				{
					count++;														
					break;
				}
			}
		}
		if(isValid(i+1,j-1) && a[i+1][j-1]==(1-player))
		{
			for(k=i+2,l=j-2;isValid(k,l)&&a[k][l]!=-1;k++,l--)
			{
				if(a[k][l]==player)
				{
					count++;														
					break;
				}
			}
		}
		if(isValid(i,j-1) && a[i][j-1]==(1-player))
		{
			for(k=j-2;k>=0&&a[i][k]!=-1;k--)
			{
				if(a[i][k]==player)
				{
					count++;												
					break;
				}
			}
		}
		if(isValid(i,j+1) && a[i][j+1]==(1-player))
		{
			for(k=j+2;k<8 &&a[i][k]!=-1;k++)
			{
				if(a[i][k]==player)
				{
					count++;														
					break;
				}
			}
		}
		if(isValid(i-1,j-1) && a[i-1][j-1]==(1-player))
		{
			for(k=i-2,l=j-2;isValid(k,l) &&a[k][l]!=-1;k--,l--)
			{
				if(a[k][l]==player)
				{
					count++;										
					break;
				}
			}
		}
		if(isValid(i-1,j+1) && a[i-1][j+1]==(1-player))
		{
			for(k=i-2,l=j+2;isValid(k,l)&&a[k][l]!=-1;k--,l++)
			{
				if(a[k][l]==player)
				{
					count++;													
					break;
				}
			}
		}
	}
	return count;
}
//void printScore(int a[][8])
//{
//	int i,j;
//	int wScore=0,bScore=0;
//	for(i=0;i<8;i++)
//	{
//		for(j=0;j<8;j++)
//		{			
//			if(a[i][j]==0){
//				bScore++;
//			}			
//			else{
//				wScore++;
//			}
//		}	
//	}
//	cout << "Black's score: " << bScore << endl;
//	cout << "White's score: " << wScore << endl;
//}
int main()
{
	int a[8][8];
	vector< vNode > v;
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			a[i][j]=-1;
		}
	}	
	int temp;
	cout << "1.Use Original Othello Configuration?\n2.Use Given Configuration?\n";
	cin >> temp;
	if(temp==2)
	{
		// int nob,now;
		// cout << "Enter number of blacks initially?: ";
		// cin >> nob;
		// cout << "Enter number of whites initially?: ";
		// cin >> now;
		// cout << "Enter pos of blacks: \n";
		// for (i=0;i<nob;i++)
		// {
		// 	int temp1,temp2;
		// 	cin >> temp1 >> temp2;
		// 	a[temp1][temp2]=0;
		// }
		// cout << "Enter pos of whites: \n";
		// for (i=0;i<now;i++)
		// {
		// 	int temp1,temp2;
		// 	cin >> temp1 >> temp2;
		// 	a[temp1][temp2]=1;
		// }
		ifstream f("matrix.txt");
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
		  {
				f >> a[i][j];
			}
		}
		// ofstream f("matrix.txt");
		// for (int i = 0; i < 8; i++)
		// {
		// 	for (int j = 0; j < 8; j++)
		//   {
		// 		f << -1 << "\t\t\t";
		// 	}
		// 	f << "\n";
		// }
	}
	else{
		a[4][4]=0;
		a[3][3]=0;
		a[3][4]=1;
		a[4][3]=1;
	}
	print(a);
	int player,computer;
	cout << "Do you want to play as \n0)Black or \n1)White?\n";
	cin >> player;
	computer=1-player;
	if(player==0)
	{		
		findMove(a,player,v);
		cout << "********************\n";
		cout << "Your moves are: \n";
		printV(v);
		int tempX,tempY;
		cout << "Enter your move(x and y co-ordinates): ";
		cin >> tempX >>tempY;
		while(!isValidMove(a,player,tempX,tempY))
		{
			cout << "Wrong Move\n";
			cout << "Enter your move(x and y co-ordinates): ";	
			cin >> tempX >>tempY;
		}
		vNode temp;
		temp.x=tempX;
		temp.y=tempY;
		for(i=0;i<v.size();i++)
		{
			if(v[i].x==tempX && v[i].y==tempY)
			{
				for(int j=0;j<v[i].dirToFlip.size();j++)
				{
					temp.dirToFlip.push_back(v[i].dirToFlip[j]);
				}
			}
		}
		flipBoard(temp,a,player);
		cout << "After Player's move:\n ";
		print(a);		
	}
	int flag=0;
	deleteV(v);
	while(findMove(a,computer,v))
	{
//		printV(v);
		int i;
		int alpha= MIN;
		int beta=MAX;
		int pos,best;
		if(computer==0)
		{
			best=MIN;
		}
		else{
			best=MAX;
		}
		int tempBoard[8][8];
		for(i=0;i<v.size();i++)
		{		
			copy(&a[0][0], &a[0][0]+64,&tempBoard[0][0]);
			if(computer==0)
			{
//				best=MIN;
				int val= minimax(tempBoard,1,false,alpha,beta,v[i],computer);
				if(best < val)
				{
					best=val;
					pos=i;
					alpha = max(alpha, best);
				}	             
	  
	            if (beta <= alpha)
	                break; 
			}
			else{
//				best=MAX;
				int val= minimax(tempBoard,1,true,alpha,beta,v[i],computer);
				if(best > val)
				{
					best=val;
					pos=i;
					beta = min(beta, best); 
				}				 
	  
	            if (beta <= alpha) 
	                break;
			}
//			cout << "***************************\n";
//			cout <<"BEST IS: "<< best << endl;		
		}
//		a[v[pos].x][v[pos].y]=computer;
//		cout << "Printing TempBoard: \n";
//		print(tempBoard);
//		cout << "Printing a: \n";
//		print(a);
		cout << "Computer's Move: " << v[pos].x << " " <<  v[pos].y << endl;
		flipBoard(v[pos],a,computer);
		cout << best << endl;
		cout << "After Computer's move:\n ";
		print(a);
		deleteV(v);
//		printScore(a);
		if(findMove(a,player,v))
		{
			cout << "********************\n";
			cout << "Your moves are: \n";
			printV(v);
			int tempX,tempY;
			cout << "Enter your move(x and y co-ordinates): ";
			cin >> tempX >>tempY;
			while(!isValidMove(a,player,tempX,tempY))
			{
				cout << "Wrong Move\n";
				cout << "Enter your move(x and y co-ordinates): ";	
				cin >> tempX >>tempY;
			}
			vNode temp;
			temp.x=tempX;
			temp.y=tempY;
			for(i=0;i<v.size();i++)
			{
				if(v[i].x==tempX && v[i].y==tempY)
				{
					for(int j=0;j<v[i].dirToFlip.size();j++)
					{
						temp.dirToFlip.push_back(v[i].dirToFlip[j]);
					}
				}
			}
			flipBoard(temp,a,player);
			cout << "After Player's move:\n ";
			print(a);
		}
		else {
			cout << "No other move left!\n";
			flag=1;
			break;
		}
		deleteV(v);
	}
	int score = getScoreOfBoard(a);
	if(computer==0)
	{
		if(score > 0)
		{
			cout << "Computer has won!\n";
		}
		else if(score==0)
		{
			cout << "It's a draw match'!\n";
		}
		else{
			cout << "You have won!\n";
		}
	}
	else{
		if(score > 0)
		{
			cout << "You have won!\n";
		}
		else if(score==0)
		{
			cout << "It's a draw match'!\n";
		}
		else{
			cout << "Computer has won!\n";
		}
	}
}

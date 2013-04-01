#include "stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;



class Matrix
{
	int n;
	int m;
	int **A;

public:

	Matrix()
	{
		

		n=4;
		m=4;

		A=new int*[n];
		for (int i=0;i<n;i++)
			A[i]=new int[m];

		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
				A[i][j]=rand()%10;

	}
	Matrix(Matrix &matr)
	{
		n=matr.n;
		m=matr.m;
		
		A=new int*[n];
		for (int i=0;i<n;i++)
			A[i]=new int[m];

		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
				A[i][j]=matr.A[i][j];	
	}

	
	Matrix operator*(Matrix &matr);
	bool Orthogonality();
	Matrix SetIdentity();
	Matrix Transpose();
	Matrix RotateX(double L);
	Matrix RotateY(double L);
	Matrix RotateZ(double L);
	Matrix Scale(int x,int y,int z);
	Matrix Translation(int x,int y,int z);


	friend ostream& operator<<(ostream &output,const Matrix &matr);
	void Random();
	
};


Matrix Matrix::operator*(Matrix &matr)
{
	Matrix temp;

	for(int i=0;i<this->n;i++)
		for(int j=0;j<matr.m;j++)
		{
			temp.A[i][j]=0;
			for (int k=0;k<matr.n;k++) 
				temp.A[i][j]+=this->A[i][k]*matr.A[k][j];
		}


	return temp;
}


void Matrix::Random()
{
	for (int i=0;i<this->n;i++)
		for (int j=0;j<m;j++)
			A[i][j]=rand()%10;
}
bool Matrix::Orthogonality()
{
	Matrix temp;
	temp.A=this->A;

	if ((temp*temp.Transpose()).A==temp.SetIdentity().A) return true;
	else return false;
}
Matrix Matrix::Transpose()
{
	Matrix temp;

	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
		{
			temp.A[i][j]=this->A[j][i];
		}

	return temp;
}
Matrix Matrix::SetIdentity()
{
	
	Matrix temp;

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			if(i==j) temp.A[i][j]=1;
			else temp.A[i][j]=0;
		}

	return temp;
	
}
Matrix Matrix::Scale(int x,int y,int z)
{
	Matrix temp;

	temp.SetIdentity();

	temp.A[0][0]=z;
	temp.A[1][1]=y;
	temp.A[2][2]=x;

	


	return (*this)*temp;
}
Matrix Matrix::RotateX(double L)
{
	Matrix temp;
	temp.SetIdentity();


		temp.A[1][1]=cos(L);
		temp.A[2][2]=cos(L);
		temp.A[3][2]=-sin(L);
		temp.A[2][3]=sin(L);


	return (*this)*temp;
}
Matrix Matrix::RotateY(double L)
{
	Matrix temp;
	temp.SetIdentity();

		temp.A[0][0]=cos(L);
		temp.A[0][2]=-sin(L);
		temp.A[3][0]=sin(L);
		temp.A[3][2]=cos(L);

	
	return (*this)*temp;
}
Matrix Matrix::RotateZ(double L)
{
	Matrix temp;
	temp.SetIdentity();



		temp.A[0][0]=cos(L);
		temp.A[1][1]=cos(L);
		temp.A[0][1]=sin(L);


	return (*this)*temp;
}
Matrix Matrix::Translation(int x,int y,int z)
{
	Matrix temp;

	temp=*this;

	temp.A[0][0]+=x;
	temp.A[1][1]+=y;
	temp.A[2][2]+=z;

	return temp;
}
ostream& operator<<(ostream &output, const Matrix &matr)
{
	for (int i=0;i<matr.n;i++)
	{
		for (int j=0;j<matr.m;j++)
		{
			output<<matr.A[i][j]<<" ";
		}
		output<<"\n\n";
	}
	cout<<endl;

	return output;
}

void Operations(Matrix m1,Matrix m2)
{
	
	cout<<"[Умножение матриц]:"<<m1*m2<<endl;
	cout<<"[Транспонирование матрицы]:"<<endl<<m1.Transpose();
	cout<<"[Матрица поворота]:"<<endl<<m1.Scale(2,3,4);
	cout<<"[Единичная матрица]:"<<endl<<m1.SetIdentity();
	if(m1.Orthogonality()) cout<<"[Ортогональны]"<<endl;
	else cout<<"[Неортогональны]"<<endl;
	cout<<"[Поворот по Х]:"<<endl<<m1.RotateX(1.0)<<endl;
	cout<<"[Поворот по Y]:"<<endl<<m1.RotateY(2.0)<<endl;
	cout<<"[Поворот по Z]:"<<endl<<m1.RotateZ(3.0)<<endl;
	cout<<"[Сдвиг]:"<<endl<<m1.Translation(2,4,3)<<endl;
}
void main()
{
	setlocale(LC_ALL,"RUS");

	Matrix m1;
	Matrix m2;


	Operations(m1,m2);

}
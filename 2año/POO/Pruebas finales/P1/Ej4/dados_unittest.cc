// dados_unittest.cc: Juan A. Romero
// A sample program demonstrating using Google C++ testing framework.
//


// This sample shows how to write a more complex unit test for a class
// that has multiple member functions.
//
// Usually, it's a good idea to have one test for each method in your
// class.  You don't have to do that exactly, but it helps to keep
// your tests organized.  You may also throw in additional tests as
// needed.

#include "dados.h"
#include "gtest/gtest.h"

// Tests the c'tor.
TEST(Dados, Constructor) {
  Dados d;
  
  EXPECT_EQ(1, d.getDado1());
  EXPECT_EQ(1, d.getDado2());
  EXPECT_EQ(2, d.getSuma());
  
}

// Tests operación lanzamiento
TEST(Dados, Lanzamiento) {
  Dados d;
  for (int i=0; i<100; i++){
  d.lanzamiento();
  EXPECT_GT(d.getDado1(), 0);
  EXPECT_LT(d.getDado1(), 7);
  EXPECT_GT(d.getDado2(), 0);
  EXPECT_LT(d.getDado2(), 7);
}

}

// Tests operación suma
TEST(Dados, Suma) {
  Dados d;
  
  EXPECT_EQ(d.getDado1()+d.getDado2(), d.getSuma());
}

// Tests modificadores
TEST(Dados, Modificadores) {
  Dados d;
  
  EXPECT_FALSE(d.setDado1(9));
  EXPECT_FALSE(d.setDado1(-9));
  EXPECT_FALSE(d.setDado2(9));
  EXPECT_FALSE(d.setDado2(-9));
  d.setDado1(3);
  EXPECT_EQ(3, d.getDado1());
  d.setDado2(2);
  EXPECT_EQ(2, d.getDado2());
  EXPECT_EQ(5, d.getSuma());
}

//Test operacion resta
TEST(Dados, Resta){
  Dados d;

  d.setDado1(1);
  d.setDado2(5);
  EXPECT_EQ(4,d.getDiferencia());
  d.setDado1(6);
  d.setDado2(3);
  EXPECT_EQ(3,d.getDiferencia());
  d.setDado1(3);
  d.setDado2(3);

}

//Test contador lanzamientos de los dados

TEST(Dados,ContadorLanzamientos){
	Dados d;

	EXPECT_EQ(0,d.getLanzamientos1());
	EXPECT_EQ(0,d.getLanzamientos2());
	d.lanzamiento();
	EXPECT_EQ(1,d.getLanzamientos1());
	EXPECT_EQ(1,d.getLanzamientos2());

	for(int i=0;i<100;i++){

 		d.setDado1(3);

	}

	EXPECT_EQ(101,d.getLanzamientos1());

	for(int i=0;i<200;i++){

 		d.setDado2(3);

	}

	EXPECT_EQ(201,d.getLanzamientos2());

}

//Test media de los dados
TEST(Dados,Medias){
	Dados d;

	EXPECT_EQ(0,d.getMedia1());
	EXPECT_EQ(0,d.getMedia2());

	d.setDado1(3);
	d.setDado1(4);
	d.setDado1(2);
	d.setDado1(1);
	d.setDado1(6);
	d.setDado1(6);
	d.setDado1(5);
	d.setDado1(3);

	EXPECT_NEAR(d.getMedia1(),3,4);

	d.setDado2(5);
	d.setDado2(4);
	d.setDado2(2);
	d.setDado2(1);

	EXPECT_EQ(3,d.getMedia2());

	int suma1=0;
	int suma2=0;
	int i=0;

	for(;i<100;i++){

		d.lanzamiento();
		suma1=suma1+d.getDado1();
		suma2=suma2+d.getDado2();

	}

	EXPECT_EQ((suma1/i),d.getMedia1());
	EXPECT_EQ((suma2/i),d.getMedia2());

}

//Test vectores de los dados ultimos
TEST(Dados,Ultimos){
	Dados d;

	int v1[5];

	for(int i=0;i<5;i++){

		v1[i]=0;

	}

	int v2[5];

	for(int i=0;i<5;i++){

		v2[i]=0;

	}

	int vv1[5];

	for(int i=0;i<5;i++){

	vv1[i]=0;

	}

	int vv2[5];

	for(int i=0;i<5;i++){

	vv2[i]=0;

	}

	d.getUltimos1(vv1);
	d.getUltimos2(vv2);

	EXPECT_EQ(v1[0],vv1[0]);
	EXPECT_EQ(v1[1],vv1[1]);
	EXPECT_EQ(v1[2],vv1[2]);
	EXPECT_EQ(v1[3],vv1[3]);
	EXPECT_EQ(v1[4],vv1[4]);

	EXPECT_EQ(v2[0],vv2[0]);
	EXPECT_EQ(v2[1],vv2[1]);
	EXPECT_EQ(v2[2],vv2[2]);
	EXPECT_EQ(v2[3],vv2[3]);
	EXPECT_EQ(v2[4],vv2[4]);

	d.setDado1(3);
	d.setDado1(4);
	d.setDado1(2);
	d.setDado1(1);
	d.setDado1(6);
	d.setDado1(6);

	d.getUltimos1(vv1);

	v1[0]=4;
	v1[1]=2;
	v1[2]=1;
	v1[3]=6;
	v1[4]=6;

	EXPECT_EQ(v1[0],vv1[0]);
	EXPECT_EQ(v1[1],vv1[1]);
	EXPECT_EQ(v1[2],vv1[2]);
	EXPECT_EQ(v1[3],vv1[3]);
	EXPECT_EQ(v1[4],vv1[4]);

	d.setDado2(4);
	d.setDado2(5);
	d.setDado2(6);
	d.setDado2(1);
	d.setDado2(2);
	d.setDado2(6);

	d.getUltimos2(vv2);

	v2[0]=5;
	v2[1]=6;
	v2[2]=1;
	v2[3]=2;
	v2[4]=6;

	EXPECT_EQ(v2[0],vv2[0]);
	EXPECT_EQ(v2[1],vv2[1]);
	EXPECT_EQ(v2[2],vv2[2]);
	EXPECT_EQ(v2[3],vv2[3]);
	EXPECT_EQ(v2[4],vv2[4]);

}


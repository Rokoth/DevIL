// MoneyTest.cpp

#include "ILTest.h"
#include <IL/il.h>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ILTest );


#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <iostream>

void ILTest::setUp()
{
  ilInit();
}


void ILTest::tearDown()
{
  const ILenum lResult = ilGetError();

  while (ilGetError() != IL_NO_ERROR) {;}

  ilResetMemory();
  CPPUNIT_ASSERT(ilGetError() == IL_NO_ERROR);

  CPPUNIT_ASSERT_MESSAGE("Received Error from ilGetError", lResult == IL_NO_ERROR);
}


void ILTest::TestilActiveImage()
{
  //Must call ilGenImages and ilBindImage for it to work
  ilActiveImage(3);
  CPPUNIT_ASSERT(ilGetError() == IL_ILLEGAL_OPERATION);
  CPPUNIT_ASSERT(ilGetError() == IL_NO_ERROR);

  ILuint MainImage = 0;
  ilGenImages(1, &MainImage);
  ilBindImage(MainImage);

  //Must have several images in the file
  ilLoadImage(".\\Data\\Cardinal.gif");

  //Number of images must be > 0
  const unsigned int lNumImages = ilGetInteger(IL_NUM_IMAGES);
  CPPUNIT_ASSERT(lNumImages > 0);
  
  //Never an error
  ilActiveImage(0);
  CPPUNIT_ASSERT(ilGetError() == IL_NO_ERROR);

  //Selects the second picture
  ilActiveImage(1);
  CPPUNIT_ASSERT(ilGetError() == IL_NO_ERROR);

  //It does not have that many images so error is reported
  ilActiveImage(2045);
  CPPUNIT_ASSERT(ilGetError() == IL_ILLEGAL_OPERATION);
}

void ILTest::TestilSaveF()
{
  FILE * lBuffer = fopen(".\\results\\result.bmp", "wb");
  ilLoadImage(".\\Data\\Logo.png");
  ilSaveF(IL_BMP,lBuffer);
  fclose(lBuffer);
}
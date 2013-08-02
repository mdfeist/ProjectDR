// DICOMConverter.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "itkImage.h"
#include "itkImageSeriesReader.h"
#include "itkGDCMImageIO.h"
#include "itkRGBAPixel.h"
#include "itkGDCMSeriesFileNames.h"

int pixelCount;
unsigned char *data;
float spacingX, spacingY, spacingZ;
int volumeWidth, volumeHeight, volumeDepth;

int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cout << "Failed."<< std::endl;
		std::cout <<"*********************************************************************" <<std::endl;
		std::cout << "Wrong number of arguments." << std::endl;
		std::cout << "application path/to/dicom/folder path/to/output/file.raw" << std::endl;
		std::cout << "*********************************************************************" <<std::endl;
		return EXIT_FAILURE;
	}

	typedef signed short    PixelType;										// How each pixel is stored
	const unsigned int      Dimension = 3;									// The number of dimensions of the data

	typedef itk::Image< PixelType, Dimension >         ImageType;			// The image type

	typedef itk::ImageSeriesReader<ImageType> ReaderType;					// Image reader type
	ReaderType::Pointer reader = ReaderType::New();							// Create the image reader
	
	typedef itk::GDCMImageIO       ImageIOType;								// IO class for reading DICOM images
	ImageIOType::Pointer dicomIO = ImageIOType::New();						// Create Image IO

	reader->SetImageIO( dicomIO );											// Set the image IO in the reader to read DICOM images

	typedef itk::GDCMSeriesFileNames NamesGeneratorType;					// Generate a sequence of filenames from a DICOM series
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();	// Creates new GDCMSeriesFileNames

	nameGenerator->SetUseSeriesDetails( true );								// If multiple volumes are being grouped as a single series for your DICOM objects
	nameGenerator->AddSeriesRestriction("0008|0021" );						// Add more restriction on the selection of a Series

	nameGenerator->SetDirectory( argv[1] );									// Give the directory to read from
	
	try
	{
		std::cout << "- The directory: " << argv[1] << std::endl;
		std::cout << "- Contains the following DICOM Series: ";

		typedef std::vector< std::string >    SeriesIdContainer;
		const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();
		SeriesIdContainer::const_iterator seriesItr = seriesUID.begin();
		SeriesIdContainer::const_iterator seriesEnd = seriesUID.end();
		while( seriesItr != seriesEnd )
		{
			std::cout << seriesItr->c_str() << std::endl;
			++seriesItr;
		}
		
		std::string seriesIdentifier;

		//single series in folder
		seriesIdentifier = seriesUID.begin()->c_str();

		std::cout << "- Now reading series: ";
		std::cout << seriesIdentifier;
		std::cout << std::endl;


		typedef std::vector< std::string >   FileNamesContainer;
		FileNamesContainer fileNames;
		fileNames = nameGenerator->GetFileNames( seriesIdentifier );

		// File names to Read
		reader->SetFileNames( fileNames );
		std::cout << "- Reading files ... " << std::endl;

		try
		{
			reader->UpdateLargestPossibleRegion();
			std::cout << "- Successfully read " << fileNames.size() << " file(s)." << std::endl;
		}
		catch (itk::ExceptionObject &ex)
		{
			std::cout << "Failed."<< std::endl;
			std::cout <<"*********************************************************************" <<std::endl;
			std::cout << ex << std::endl;
			std::cout << "*********************************************************************" <<std::endl;
			return EXIT_FAILURE;
		}

		//Test Function: Get Dimention values
		typedef itk::Image< PixelType, 3 >   ImageType;
		ImageType::Pointer image = reader->GetOutput();

		ImageType::RegionType region = image->GetLargestPossibleRegion();
		ImageType::SizeType size = region.GetSize();
		ImageType::SpacingType spacing = image->GetSpacing();

		// Pointer to the start of the Image
		signed short * bufferPointer = reader->GetOutput()->GetBufferPointer();

		// Get number of pixels in image
		pixelCount = size[0] * size[1] *size[2];

		volumeWidth = size[0];
		volumeHeight = size[1];
		volumeDepth = size[2];

		spacingX = spacing[0];
		spacingY = spacing[1];
		spacingZ = spacing[2];

		std::cout << "- Volume Size: " 
			<< "[" 
			<< volumeWidth << ", "
			<< volumeHeight << ", "
			<< volumeDepth
			<< "]" << std::endl;

		if (data != NULL) {
			delete[] data;
			data = NULL;
		}

		// Create array for iso values
		data = new unsigned char[pixelCount];
		memset(data, 0, pixelCount);

		std::cout << "- Normalizing data" << std::endl; 

		float min = -1000.f;
		float max = 1000.f;

		// Normalize values
		for (unsigned int i = 0; i < pixelCount; i++)
		{
			float normal = ((float)bufferPointer[i] - min)/(max - min);

			if (normal < 0.f)
				normal = 0.f;
			else if (normal > 1.f)
				normal = 1.f;

			data[i] = (unsigned char)(255.f*normal);
		}
	}
	catch (itk::ExceptionObject &ex)
    {
		std::cout << ex << std::endl;
		return EXIT_FAILURE;
    }
	
	FILE* dataFile = NULL;
	fopen_s(&dataFile, argv[2], "wb");										// Opens file

	if (dataFile) {															// Checks if file was able to open
		std::cout << "- Saving File" << std::endl; 
		fwrite(&spacingX, sizeof(float), 1, dataFile);						// Write X spacing size
		fwrite(&spacingY, sizeof(float), 1, dataFile);						// Write Y spacing size 
		fwrite(&spacingZ, sizeof(float), 1, dataFile);						// Write Z spacing size
		fwrite(&volumeWidth, sizeof(int), 1, dataFile);						// Write volume width
		fwrite(&volumeHeight, sizeof(int), 1, dataFile);					// Write volume height
		fwrite(&volumeDepth, sizeof(int), 1, dataFile);						// Write volume depth
		fwrite(data, sizeof(unsigned char), pixelCount, dataFile);			// Write volume data from file

		fclose(dataFile);
	}

	return 0;
}


//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ConvertTexture.h"
#include "meshData.h"
#include "GLTF.h"
#include "File.h"
#include "stb_image.h"

using namespace tinygltf;

namespace Azul
{

    void gltReadTGABits(const char *pFileName, textureData &textData);
    void gltReadPNGBits(const char *pFileName, textureData &textData);

    // Define targa header. This is only used locally.
#pragma pack(1)
    typedef struct
    {
        char	identsize;               // Size of ID field that follows header (0)
        char	colorMapType;            // 0 = None, 1 = paletted
        char	imageType;               // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
        unsigned short	colorMapStart;   // First colour map entry
        unsigned short	colorMapLength;  // Number of colors
        unsigned char 	colorMapBits;    // bits per palette entry
        unsigned short	xstart;          // image x origin
        unsigned short	ystart;          // image y origin
        unsigned short	width;           // width in pixels
        unsigned short	height;          // height in pixels
        char	bits;                    // bits per pixel (8 16, 24, 32)
        char	descriptor;              // image descriptor
    } TGAHEADER;
#pragma pack(8)

    void ConvertTexturePNG(const char *const pFileName)
    {
        assert(pFileName);
        Trace::out("ConvertTexturePNG(%s): \n", pFileName);

        // Strip the extension .tga off the name
        unsigned int len = strlen(pFileName);
        char *pTmp = new char[len + 1]();
        memset(pTmp, 0, len);
        memcpy(pTmp, pFileName, len - strlen(".png"));

        // base name
        std::string BaseName = pTmp;
        delete[] pTmp;

        // runtime model
        meshData  runModel;

        //---------------------------------
        // Model Name
        //---------------------------------
        const char *pMeshName = "-PNG-";
        memcpy_s(runModel.pMeshName, meshData::FILE_NAME_SIZE, pMeshName, strlen(pMeshName));


        runModel.text_color.enabled = true;
        runModel.text_color.textType = textureData::TEXTURE_TYPE::PNG;
        runModel.text_color.magFilter = textureData::TEXTURE_MAG_FILTER::MAG_LINEAR;
        runModel.text_color.minFilter = textureData::TEXTURE_MIN_FILTER::MIN_LINEAR;
        runModel.text_color.wrapS = textureData::TEXTURE_WRAP::WRAP_CLAMP_TO_EDGE;
        runModel.text_color.wrapT = textureData::TEXTURE_WRAP::WRAP_CLAMP_TO_EDGE;
        runModel.text_color.pixel_type = textureData::TEXTURE_COMPONENT::UNSIGNED_BYTE;
        runModel.text_color.as_is = false;

        memcpy_s(runModel.text_color.pFileName, textureData::FILE_NAME_SIZE, pFileName, strlen(pFileName));


        gltReadPNGBits(pFileName, runModel.text_color);


        //Trace::out("--------------\n");
        //Trace::out("--------------\n");
        //Trace::out("--------------\n");

     //   runModel.Print("mA");
        meshData_proto mA_proto;
        runModel.Serialize(mA_proto);

        //Trace::out("\n");
        //Trace::out("message size: %d \n", mA_proto.ByteSizeLong());
        //Trace::out("\n");


        // -------------------------------
        //  Write to file
        //--------------------------------

        File::Handle fh;
        File::Error err;

        // Create output name
        const char *pProtoFileType = nullptr;
        bool status = GLTF::GetAzulProtoType(pProtoFileType, runModel);
        assert(status);

        std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";

        err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
        assert(err == File::Error::SUCCESS);

        std::string strOut;
        mA_proto.SerializeToString(&strOut);

        File::Write(fh, strOut.data(), strOut.length());
        assert(err == File::Error::SUCCESS);

        err = File::Close(fh);
        assert(err == File::Error::SUCCESS);

        // -------------------------------
        // Read and recreate model data
        // -------------------------------
        Trace::out("   --> %s\n", OutputFileName.c_str());
        err = File::Open(fh, OutputFileName.c_str(), File::Mode::READ);
        assert(err == File::Error::SUCCESS);

        err = File::Seek(fh, File::Position::END, 0);
        assert(err == File::Error::SUCCESS);

        DWORD FileLength;
        err = File::Tell(fh, FileLength);
        assert(err == File::Error::SUCCESS);

        char *poNewBuff = new char[FileLength]();
        assert(poNewBuff);

        err = File::Seek(fh, File::Position::BEGIN, 0);
        assert(err == File::Error::SUCCESS);

        err = File::Read(fh, poNewBuff, FileLength);
        assert(err == File::Error::SUCCESS);

        err = File::Close(fh);
        assert(err == File::Error::SUCCESS);

        //Trace::out("--------------\n");
        //Trace::out("--------------\n");
        //Trace::out("--------------\n");

        std::string strIn(poNewBuff, FileLength);
        meshData_proto mB_proto;

        mB_proto.ParseFromString(strIn);

        meshData mB;
        mB.Deserialize(mB_proto);
        // mB.Print("mB");

        delete[] poNewBuff;

    }


    void ConvertTextureTGA(const char *const pFileName)
    {
        assert(pFileName);

        Trace::out("ConvertTextureTGA(%s): \n",pFileName);

        // Strip the extension .tga off the name
        unsigned int len = strlen(pFileName);
        char *pTmp = new char[len + 1]();
        memset(pTmp, 0, len);
        memcpy(pTmp, pFileName, len - strlen(".tga"));

        // base name
        std::string BaseName = pTmp;
        delete[] pTmp;

        // runtime model
        meshData  runModel;

        //---------------------------------
        // Model Name
        //---------------------------------
        const char *pMeshName = "-TGA-";
        memcpy_s(runModel.pMeshName, meshData::FILE_NAME_SIZE, pMeshName, strlen(pMeshName));


        runModel.text_color.enabled = true;
        runModel.text_color.textType = textureData::TEXTURE_TYPE::TGA;
        runModel.text_color.magFilter = textureData::TEXTURE_MAG_FILTER::MAG_LINEAR;
        runModel.text_color.minFilter = textureData::TEXTURE_MIN_FILTER::MIN_LINEAR;
        runModel.text_color.wrapS = textureData::TEXTURE_WRAP::WRAP_CLAMP_TO_EDGE;
        runModel.text_color.wrapT = textureData::TEXTURE_WRAP::WRAP_CLAMP_TO_EDGE;
        runModel.text_color.pixel_type = textureData::TEXTURE_COMPONENT::UNSIGNED_BYTE;
        runModel.text_color.as_is = false;

        memcpy_s(runModel.text_color.pFileName, textureData::FILE_NAME_SIZE, pFileName, strlen(pFileName));


        gltReadTGABits(pFileName, runModel.text_color);


        //Trace::out("--------------\n");
        //Trace::out("--------------\n");
        //Trace::out("--------------\n");

     //   runModel.Print("mA");
        meshData_proto mA_proto;
        runModel.Serialize(mA_proto);

        //Trace::out("\n");
        //Trace::out("message size: %d \n", mA_proto.ByteSizeLong());
        //Trace::out("\n");


        // -------------------------------
        //  Write to file
        //--------------------------------

        File::Handle fh;
        File::Error err;

        // Create output name
        const char *pProtoFileType = nullptr;
        bool status = GLTF::GetAzulProtoType(pProtoFileType, runModel);
        assert(status);

        std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";
        Trace::out("   --> %s\n", OutputFileName.c_str());
        err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
        assert(err == File::Error::SUCCESS);

        std::string strOut;
        mA_proto.SerializeToString(&strOut);

        File::Write(fh, strOut.data(), strOut.length());
        assert(err == File::Error::SUCCESS);

        err = File::Close(fh);
        assert(err == File::Error::SUCCESS);

        // -------------------------------
        // Read and recreate model data
        // -------------------------------

        err = File::Open(fh, OutputFileName.c_str(), File::Mode::READ);
        assert(err == File::Error::SUCCESS);

        err = File::Seek(fh, File::Position::END, 0);
        assert(err == File::Error::SUCCESS);

        DWORD FileLength;
        err = File::Tell(fh, FileLength);
        assert(err == File::Error::SUCCESS);

        char *poNewBuff = new char[FileLength]();
        assert(poNewBuff);

        err = File::Seek(fh, File::Position::BEGIN, 0);
        assert(err == File::Error::SUCCESS);

        err = File::Read(fh, poNewBuff, FileLength);
        assert(err == File::Error::SUCCESS);

        err = File::Close(fh);
        assert(err == File::Error::SUCCESS);

        //Trace::out("--------------\n");
        //Trace::out("--------------\n");
        //Trace::out("--------------\n");

        std::string strIn(poNewBuff, FileLength);
        meshData_proto mB_proto;

        mB_proto.ParseFromString(strIn);

        meshData mB;
        mB.Deserialize(mB_proto);
        // mB.Print("mB");

        delete[] poNewBuff;

    }



    //-----------------------------------------------------------------------------
    // Allocate memory and load targa bits. Returns pointer to new buffer,
    // height, and width of texture, and the OpenGL format of data.
    // Call free() on buffer when finished!
    // This only works on pretty vanilla targas... 8, 24, or 32 bit color
    // only, no palettes, no RLE encoding.
    //-----------------------------------------------------------------------------
    void gltReadTGABits(const char *pFileName, textureData &textData)
    {
        TGAHEADER tgaHeader;        // TGA file header
        unsigned long lImageSize;   // Size in bytes of image
        short sDepth;               // Pixel depth;
        char *pBits = nullptr;      // Pointer to bits

        // Default/Failed values
        unsigned int Width = 0;
        unsigned int Height = 0;
        textureData::TEXTURE_EFORMAT eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_RGB;
        textureData::TEXTURE_NCOMPONENT nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB;

        // Attempt to open the file
        File::Handle fh;
        File::Error err;

        err = File::Open(fh, pFileName, File::Mode::READ);
        assert(err == File::Error::SUCCESS);

        err = File::Read(fh, &tgaHeader, sizeof(TGAHEADER));
        assert(err == File::Error::SUCCESS);


        // Get width, height, and depth of texture
        Width = tgaHeader.width;
        Height = tgaHeader.height;
        sDepth = tgaHeader.bits / 8;

        // Put some validity checks here. Very simply, I only understand
        // or care about 8, 24, or 32 bit targa's.
        if(tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
        {
            assert(false);
        }

        // Calculate size of image buffer
        lImageSize = (unsigned int)tgaHeader.width * (unsigned int)tgaHeader.height * (unsigned int)sDepth;

        pBits = new char[lImageSize * sizeof(char)]();
        assert(pBits);

        err = File::Read(fh, pBits, lImageSize);
        assert(err == File::Error::SUCCESS);

        err = File::Close(fh);
        assert(err == File::Error::SUCCESS);


        // Set OpenGL format expected
        switch(sDepth)
        {

        case 3:     // Most likely case
            eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_BGR;
            nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB;
            break;

        case 4:
            eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_BGRA;
            nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA;
            break;

        case 1:
            assert(false);
            // bad case - keenan - commented out
            //  eFormat = GL_LUMINANCE;
            //  iComponents = GL_LUMINANCE;
            break;

        default:        // RGB
            // If on the iPhone, TGA's are BGR, and the iPhone does not 
            // support BGR without alpha, but it does support RGB,
            // so a simple swizzle of the red and blue bytes will suffice.
            // For faster iPhone loads however, save your TGA's with an Alpha!

            break;
        }

        textData.eFormat = eFormat;
        textData.nComponent = nComponents;
        textData.width = Width;
        textData.height = Height;
        textData.component = (unsigned int)sDepth;
        textData.bits = (unsigned int)tgaHeader.bits;
        textData.dataSize = lImageSize;
        textData.poData = (unsigned char *)pBits;

    }

    void gltReadPNGBits(const char *pFileName, textureData &textData)
    {

        unsigned long ImageSize;   // Size in bytes of image
        unsigned char *pBits = nullptr;      // Pointer to bits

        // Default/Failed values
        int Width = 0;
        int Height = 0;
        int comp;
       // int req_comp = 3;

        textureData::TEXTURE_EFORMAT eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_RGB;
        textureData::TEXTURE_NCOMPONENT nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB;

        pBits = stbi_load(pFileName, &Width, &Height, &comp, 0);

        ImageSize = (unsigned int)(Width * Height * comp);
        // Set OpenGL format expected
        switch(comp)
        {

        case 3:     // Most likely case
            eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_RGB;
            nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB;
            break;

        case 4:
            eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_RGBA;
            nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA;
            break;

        case 1:
            assert(false);
            // bad case - keenan - commented out
            //  eFormat = GL_LUMINANCE;
            //  iComponents = GL_LUMINANCE;
            break;

        default:        // RGB
            // If on the iPhone, TGA's are BGR, and the iPhone does not 
            // support BGR without alpha, but it does support RGB,
            // so a simple swizzle of the red and blue bytes will suffice.
            // For faster iPhone loads however, save your TGA's with an Alpha!

            break;
        }

        textData.eFormat = eFormat;
        textData.nComponent = nComponents;
        textData.width = (unsigned int)Width;
        textData.height = (unsigned int)Height;
        textData.component = (unsigned int)comp;
        textData.bits = (unsigned int)8*comp;
        textData.dataSize = ImageSize;
        textData.poData = (unsigned char *)pBits;

    }

}

// --- End of File ---

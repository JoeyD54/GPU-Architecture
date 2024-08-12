//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TextureMan.h"
#include "textureDataOpenGL.h"
#include "File.h"

namespace Azul
{
    TextureMan *TextureMan::posInstance = nullptr;

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
    TextureMan::TextureMan(int reserveNum, int reserveGrow)
        : ManBase(reserveGrow)
    {
        // Preload the reserve
        this->proFillReservedPool(reserveNum);

        // initialize derived data here
        this->poNodeCompare = new Texture();
    }

    TextureMan::~TextureMan()
    {
        delete this->poNodeCompare;
        this->poNodeCompare = nullptr;

        // iterate through the list and delete
        Iterator *pIt = this->baseGetActiveIterator();

        DLink *pNode = pIt->First();

        // Walk through the nodes
        while(!pIt->IsDone())
        {
            Texture *pDeleteMe = (Texture *)pIt->Curr();
            pNode = pIt->Next();
            delete pDeleteMe;
        }

        pIt = this->baseGetReserveIterator();

        pNode = pIt->First();

        // Walk through the nodes
        while(!pIt->IsDone())
        {
            Texture *pDeleteMe = (Texture *)pIt->Curr();
            pNode = pIt->Next();
            delete pDeleteMe;
        }
    }

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
    void TextureMan::Create(int reserveNum, int reserveGrow)
    {
        // make sure values are ressonable 
        assert(reserveNum >= 0);
        assert(reserveGrow > 0);

        // initialize the singleton here
        assert(posInstance == nullptr);

        // Do the initialization
        if(posInstance == nullptr)
        {
            posInstance = new TextureMan(reserveNum, reserveGrow);
        }

    }

    void TextureMan::Destroy()
    {
        TextureMan *pMan = TextureMan::privGetInstance();
        assert(pMan != nullptr);
        AZUL_UNUSED_VAR(pMan);

        delete TextureMan::posInstance;
        TextureMan::posInstance = nullptr;
    }
    void TextureMan::Add(Texture::Name _name, Texture *pTexture)
    {
        assert(pTexture);
        pTexture->name = _name;
    }

    Texture *TextureMan::Add(meshData &mB)
    {
        TextureMan *pMan = TextureMan::privGetInstance();

        GLuint               textureID;
        GLuint *pTextureID = &textureID;

        // Load the texture and get the textureID
        pMan->privLoadTexture(mB, pTextureID);

        Texture *pNode = (Texture *)pMan->baseAddToFront();
        assert(pNode != nullptr);

        // Initialize the date
        pNode->Set
        (
            mB.text_color.pFileName,
            Texture::Name::PROTO_LOAD,
            textureID,
            textureDataOpenGL::Get(mB.text_color.minFilter),
            textureDataOpenGL::Get(mB.text_color.magFilter),
            textureDataOpenGL::Get(mB.text_color.wrapS),
            textureDataOpenGL::Get(mB.text_color.wrapT),
            mB.text_color.width,
            mB.text_color.height
        );

        return pNode;
    }


    Texture *TextureMan::Add(const char *const pMeshFileName, Texture::Name name)
    {
        TextureMan *pMan = TextureMan::privGetInstance();

        GLuint               textureID;
        GLuint *pTextureID = &textureID;

        // Load the texture and get the textureID

        // -------------------------------
        // Read and recreate model data
        // -------------------------------

        File::Handle fh;
        File::Error err;



        assert(pMeshFileName);
        const char *pPath = "Data\\";
        size_t size = strlen(pPath) + strlen(pMeshFileName) + 1;
        char *pFileName = new char[size]();
        memset(pFileName, 0, size);
        strcat_s(pFileName, size, pPath);
        strcat_s(pFileName, size, pMeshFileName);


        err = File::Open(fh, pFileName, File::Mode::READ);
        assert(err == File::Error::SUCCESS);

        delete[] pFileName;

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

        std::string strIn(poNewBuff, FileLength);
        meshData_proto mB_proto;

        mB_proto.ParseFromString(strIn);

        meshData mB;
        mB.Deserialize(mB_proto);
       // mB.Print("mB");

        delete[] poNewBuff;

        pMan->privLoadTexture(mB, pTextureID);

        Texture *pNode = (Texture *)pMan->baseAddToFront();
        assert(pNode != nullptr);

        // Initialize the date
        pNode->Set
        (
            mB.text_color.pFileName,
            name,
            textureID,
            textureDataOpenGL::Get(mB.text_color.minFilter),
            textureDataOpenGL::Get(mB.text_color.magFilter),
            textureDataOpenGL::Get(mB.text_color.wrapS),
            textureDataOpenGL::Get(mB.text_color.wrapT),
            mB.text_color.width,
            mB.text_color.height
        );

        return pNode;
    }



    Texture *TextureMan::Find(Texture::Name _name)
    {
        TextureMan *pMan = TextureMan::privGetInstance();
        assert(pMan != nullptr);

        // Compare functions only compares two Nodes

        // So:  Use the Compare Node - as a reference
        //      use in the Compare() function
        pMan->poNodeCompare->name = _name;

        Texture *pData = (Texture *)pMan->baseFind(pMan->poNodeCompare);
        return pData;
    }

    GLuint TextureMan::FindID(Texture::Name name)
    {
        TextureMan *pMan = TextureMan::privGetInstance();
        assert(pMan != nullptr);

        Texture *pTexture = pMan->Find(name);
        if(pTexture == nullptr)
        {
            pTexture = pMan->Find(Texture::Name::HOT_PINK);
        }

        return pTexture->textureID;
    }

    void TextureMan::Remove(Texture *pNode)
    {
        assert(pNode != nullptr);

        TextureMan *pMan = TextureMan::privGetInstance();
        assert(pMan != nullptr);

        pMan->baseRemove(pNode);
    }

    void TextureMan::Dump()
    {
        TextureMan *pMan = TextureMan::privGetInstance();
        assert(pMan != nullptr);

        pMan->baseDump();
    }

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
    TextureMan *TextureMan::privGetInstance()
    {
        // Safety - this forces users to call Create() first before using class
        assert(posInstance != nullptr);

        return posInstance;
    }

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
    DLink *TextureMan::derivedCreateNode()
    {
        DLink *pNodeBase = new Texture();
        assert(pNodeBase != nullptr);

        return pNodeBase;
    }

    void TextureMan::privLoadTexture(meshData &mB, GLuint *&textureID)
    {
        // Get an ID, for textures (OpenGL poor man's handle)
        glGenTextures(1, textureID);

        // Bind it.
        glBindTexture(GL_TEXTURE_2D, *textureID);

        // Loat the texture
        assert(mB.text_color.as_is == false);
        this->privLoadRawTexture(mB);
    }

    bool TextureMan::privLoadRawTexture(meshData &mB)
    {
        void *pBits = mB.text_color.poData;
        assert(pBits);

        int nWidth = (int)mB.text_color.width;
        int nHeight = (int)mB.text_color.height;

        // Hard to verify.. best guess.. input RGBA, output RGBA
        int nComponents = this->privGetOpenGLValue(mB.text_color.nComponent);
        GLenum eFormat = this->privGetOpenGLValue(mB.text_color.eFormat);
        
        GLint minFilter = (GLint)textureDataOpenGL::Get(mB.text_color.minFilter);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)textureDataOpenGL::Get(mB.text_color.wrapS));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)textureDataOpenGL::Get(mB.text_color.wrapT));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)textureDataOpenGL::Get(mB.text_color.minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)textureDataOpenGL::Get(mB.text_color.magFilter));

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

        if(minFilter == GL_LINEAR_MIPMAP_LINEAR ||
            minFilter == GL_LINEAR_MIPMAP_NEAREST ||
            minFilter == GL_NEAREST_MIPMAP_LINEAR ||
            minFilter == GL_NEAREST_MIPMAP_NEAREST)
            glGenerateMipmap(GL_TEXTURE_2D);

        return true;
    }

    GLenum TextureMan::privGetOpenGLValue(textureData::TEXTURE_EFORMAT eFormat) const
    {
        GLenum val = 0;

        switch(eFormat)
        {
        case textureData::TEXTURE_EFORMAT::EFORMAT_BGR:
            val = GL_BGR;
            break;

        case textureData::TEXTURE_EFORMAT::EFORMAT_BGRA:
            val = GL_BGRA;
            break;

        case textureData::TEXTURE_EFORMAT::EFORMAT_RGB:
            val = GL_RGB;
            break;

        case textureData::TEXTURE_EFORMAT::EFORMAT_RGBA:
            val = GL_RGBA;
            break;

        default:
            assert(false);
        }

        return val;
    }

    GLint TextureMan::privGetOpenGLValue(textureData::TEXTURE_NCOMPONENT nComponent) const
    {
        GLint val = 0;

        switch(nComponent)
        {
        case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGR:
            val = GL_BGR;
            break;

        case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA:
            val = GL_BGRA;
            break;

        case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB:
            val = GL_RGB;
            break;

        case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA:
            val = GL_RGBA;
            break;

        default:
            assert(false);
        }

        return val;
    }

}

// --- End of File ---


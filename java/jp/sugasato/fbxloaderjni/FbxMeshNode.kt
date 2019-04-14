package jp.sugasato.fbxloaderjni

class FbxMeshNode(nativecontext:Long) {

    private var nativeContext: Long = 0
    private var NumDeformer: Int = 0
    private var deformer: Array<Deformer?> = arrayOfNulls(256)

    private external fun getNameLengthJNI(nativecontext: Long): Int
    private external fun GetNameJNI(nativecontext: Long, name: CharArray)
    private external fun GetNumVerticesJNI(nativecontext: Long): Int
    private external fun GetVerticesJNI(nativecontext: Long, inArr: DoubleArray)
    private external fun GetNumPolygonVerticesJNI(nativecontext: Long): Int
    private external fun GetPolygonVerticesJNI(nativecontext: Long, inArr: IntArray)
    private external fun GetNumPolygonJNI(nativecontext: Long): Int
    private external fun getPolygonSizeJNI(nativecontext: Long, pindex: Int): Int
    private external fun GetNumMaterialJNI(nativecontext: Long): Int
    private external fun getMaterialNameLengthJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getMaterialNameJNI(nativecontext: Long, layerIndex: Int, name: CharArray)
    private external fun getMaterialMappingInformationTypeLengthJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getMaterialMappingInformationTypeJNI(nativecontext: Long, layerIndex: Int, name: CharArray)
    private external fun getMaterialNoOfPolygonJNI(nativecontext: Long, polygonNo: Int, layerIndex: Int): Int
    private external fun getDiffuseTextureNameLengthJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getDiffuseTextureNameJNI(nativecontext: Long, layerIndex: Int, name: CharArray)
    private external fun getNormalTextureNameLengthJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getNormalTextureNameJNI(nativecontext: Long, layerIndex: Int, name: CharArray)
    private external fun getDiffuseColorJNI(nativecontext: Long, layerIndex: Int, colIndex: Int): Double
    private external fun getSpecularColorJNI(nativecontext: Long, layerIndex: Int, colIndex: Int): Double
    private external fun getAmbientColorJNI(nativecontext: Long, layerIndex: Int, colIndex: Int): Double
    private external fun getNumNormalJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getNormalNameLengthJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getNormalNameJNI(nativecontext: Long, layerIndex: Int, name: CharArray)
    private external fun getNormalMappingInformationTypeLengthJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getNormalMappingInformationTypeJNI(nativecontext: Long, layerIndex: Int, name: CharArray)
    private external fun getNormalJNI(nativecontext: Long, layerIndex: Int, inArr: DoubleArray)
    private external fun getNumUVJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getUVNameLengthJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getUVNameJNI(nativecontext: Long, layerIndex: Int, name: CharArray)
    private external fun getUVMappingInformationTypeLengthJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getUVMappingInformationTypeJNI(nativecontext: Long, layerIndex: Int, name: CharArray)
    private external fun getUVJNI(nativecontext: Long, layerIndex: Int, inArr: DoubleArray)
    private external fun getNumUVindexJNI(nativecontext: Long, layerIndex: Int): Int
    private external fun getUVindexJNI(nativecontext: Long, layerIndex: Int, inArr: IntArray)
    private external fun getAlignedUVJNI(nativecontext: Long, layerIndex: Int, inArr: DoubleArray)
    private external fun getNumDeformerJNI(nativecontext: Long): Int
    private external fun getDeformerPointerJNI(nativecontext: Long, defoIndex: Int): Long

    init {
        nativeContext = nativecontext
        NumDeformer = getNumDeformerJNI(nativeContext)
        for (i in 0 until NumDeformer) {
            deformer[i] = Deformer(getDeformerPointerJNI(nativeContext, i))
        }
    }

    fun GetName(): CharArray? {
        val len = getNameLengthJNI(nativeContext)
        if (len == 0) return null
        val name = CharArray(len)
        GetNameJNI(nativeContext, name)
        return name
    }

    fun GetNumVertices(): Int {
        return GetNumVerticesJNI(nativeContext);
    }

    fun GetVertices(): DoubleArray {
        val arr = DoubleArray(GetNumVertices() * 3)
        GetVerticesJNI(nativeContext, arr)
        return arr
    }

    fun GetNumPolygonVertices(): Int {
        return GetNumPolygonVerticesJNI(nativeContext);
    }

    fun GetPolygonVertices(): IntArray? {
        val arr = IntArray(GetNumPolygonVertices())
        GetPolygonVerticesJNI(nativeContext, arr)
        return arr
    }

    fun GetNumPolygon(): Int {
        return GetNumPolygonJNI(nativeContext)
    }

    fun getPolygonSize(pind: Int): Int {
        return getPolygonSizeJNI(nativeContext, pind)
    }

    fun GetNumMaterial(): Int {
        return GetNumMaterialJNI(nativeContext)
    }

    //Material
    fun getMaterialName(layerIndex: Int): CharArray? {
        val len = getMaterialNameLengthJNI(nativeContext, layerIndex)
        if (len == 0) return null
        val name = CharArray(len)
        getMaterialNameJNI(nativeContext, layerIndex, name)
        return name
    }

    fun getMaterialMappingInformationType(layerIndex: Int): CharArray? {
        val len = getMaterialMappingInformationTypeLengthJNI(nativeContext, layerIndex)
        if (len == 0) return null
        val name = CharArray(len)
        getMaterialMappingInformationTypeJNI(nativeContext, layerIndex, name)
        return name
    }

    fun getMaterialNoOfPolygon(polygonNo: Int, layerIndex: Int): Int {
        return getMaterialNoOfPolygonJNI(nativeContext, polygonNo, layerIndex)
    }

    fun getDiffuseTextureName(layerIndex: Int): CharArray? {
        val len = getDiffuseTextureNameLengthJNI(nativeContext, layerIndex)
        if (len == 0) return null
        val name = CharArray(len)
        getDiffuseTextureNameJNI(nativeContext, layerIndex, name)
        return name
    }

    fun getNormalTextureName(layerIndex: Int): CharArray? {
        val len = getNormalTextureNameLengthJNI(nativeContext, layerIndex)
        if (len == 0) return null
        val name = CharArray(len)
        getNormalTextureNameJNI(nativeContext, layerIndex, name)
        return name
    }

    fun getDiffuseColor(layerIndex: Int, colIndex: Int): Double {
        return getDiffuseColorJNI(nativeContext, layerIndex, colIndex)
    }

    fun getSpecularColor(layerIndex: Int, colIndex: Int): Double {
        return getSpecularColorJNI(nativeContext, layerIndex, colIndex)
    }

    fun getAmbientColor(layerIndex: Int, colIndex: Int): Double {
        return getAmbientColorJNI(nativeContext, layerIndex, colIndex)
    }

    //Normal
    fun getNumNormal(layerIndex: Int): Int {
        return getNumNormalJNI(nativeContext, layerIndex)
    }

    fun getNormalName(layerIndex: Int): CharArray? {
        val len = getNormalNameLengthJNI(nativeContext, layerIndex)
        if (len == 0) return null
        val name = CharArray(len)
        getNormalNameJNI(nativeContext, layerIndex, name)
        return name
    }

    fun getNormalMappingInformationType(layerIndex: Int): CharArray? {
        val len = getNormalMappingInformationTypeLengthJNI(nativeContext, layerIndex)
        if (len == 0) return null
        val name = CharArray(len)
        getNormalMappingInformationTypeJNI(nativeContext, layerIndex, name)
        return name
    }

    fun getNormal(layerIndex: Int): DoubleArray? {
        val arr = DoubleArray(getNumNormal(layerIndex))
        getNormalJNI(nativeContext, layerIndex, arr)
        return arr
    }

    //UV
    fun getNumUV(layerIndex: Int): Int {
        return getNumUVJNI(nativeContext, layerIndex)
    }

    fun getUVName(layerIndex: Int): CharArray? {
        val len = getUVNameLengthJNI(nativeContext, layerIndex)
        if (len == 0) return null
        val name = CharArray(len)
        getUVNameJNI(nativeContext, layerIndex, name)
        return name
    }

    fun getUVMappingInformationType(layerIndex: Int): CharArray? {
        val len = getUVMappingInformationTypeLengthJNI(nativeContext, layerIndex)
        if (len == 0) return null
        val name = CharArray(len)
        getUVMappingInformationTypeJNI(nativeContext, layerIndex, name)
        return name
    }

    fun getUV(layerIndex: Int): DoubleArray? {
        val arr = DoubleArray(getNumUV(layerIndex))
        getUVJNI(nativeContext, layerIndex, arr)
        return arr
    }

    fun getNumUVindex(layerIndex: Int): Int {
        return getNumUVindexJNI(nativeContext, layerIndex)
    }

    fun getUVindex(layerIndex: Int): IntArray? {
        val arr = IntArray(getNumUVindex(layerIndex))
        getUVindexJNI(nativeContext, layerIndex, arr)
        return arr
    }

    fun getAlignedUV(layerIndex: Int): DoubleArray? {
        val arr = DoubleArray(getNumUVindex(layerIndex) * 2)
        getAlignedUVJNI(nativeContext, layerIndex, arr)
        return arr
    }

    //Deformer
    fun GetNumDeformer(): Int {
        return NumDeformer
    }

    fun getDeformer(index: Int): Deformer? {
        return deformer[index]
    }
}
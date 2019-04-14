package jp.sugasato.fbxloaderjni

class Deformer(nativecontext:Long) {

    private var nativeContext: Long = 0

    private external fun getNameLengthJNI(nativecontext: Long): Int
    private external fun getNameJNI(nativecontext: Long, name: CharArray)
    private external fun getIndicesCntJNI(nativecontext: Long): Int
    private external fun GetIndicesJNI(nativecontext: Long, inArr: IntArray)
    private external fun GetWeightsJNI(nativecontext: Long, inArr: DoubleArray)
    private external fun getTransformLinkMatrixJNI(nativecontext: Long, y: Int, x: Int): Double
    private external fun EvaluateLocalTransformJNI(nativecontext: Long, time: Long)
    private external fun EvaluateGlobalTransformJNI(nativecontext: Long, time: Long)
    private external fun getEvaluateLocalTransformJNI(nativecontext: Long, y: Int, x: Int): Double
    private external fun getEvaluateGlobalTransformJNI(nativecontext: Long, y: Int, x: Int): Double

    init {
        nativeContext = nativecontext
    }

    fun getName(): CharArray? {
        val len = getNameLengthJNI(nativeContext)
        if (len == 0) return null
        val name = CharArray(len)
        getNameJNI(nativeContext, name)
        return name
    }

    fun getIndicesCnt(): Int {
        return getIndicesCntJNI(nativeContext)
    }

    fun GetIndices(): IntArray? {
        val arr = IntArray(getIndicesCnt())
        GetIndicesJNI(nativeContext, arr)
        return arr
    }

    fun GetWeights(): DoubleArray? {
        val arr = DoubleArray(getIndicesCnt())
        GetWeightsJNI(nativeContext, arr)
        return arr
    }

    fun getTransformLinkMatrix(y: Int, x: Int): Double {
        return getTransformLinkMatrixJNI(nativeContext, y, x)
    }

    fun getTimeFRAMES60(frame: Int): Long {
        return frame * 769769300L
    }

    fun getTimeFRAMES30(frame: Int): Long {
        return frame * 1539538600L
    }

    fun EvaluateLocalTransform(time: Long) {
        EvaluateLocalTransformJNI(nativeContext, time)
    }

    fun EvaluateGlobalTransform(time: Long) {
        EvaluateGlobalTransformJNI(nativeContext, time)
    }

    fun getEvaluateLocalTransform(y: Int, x: Int): Double {
        return getEvaluateLocalTransformJNI(nativeContext, y, x)
    }

    fun getEvaluateGlobalTransform(y: Int, x: Int): Double {
        return getEvaluateGlobalTransformJNI(nativeContext, y, x)
    }
}
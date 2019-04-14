package jp.sugasato.fbxloaderjni

import android.content.Context
import java.io.InputStream

//jni読み込み一番最初に実行
fun loadFbxLoader() {
    System.loadLibrary("fbxloaderjni-lib")
}

class FbxLoader {

    private var nativeContext: Long = 0
    private var NumMesh = 0
    private var Mesh: Array<FbxMeshNode?>? = null
    private var NumDeformer = 0
    private var deformer: Array<Deformer?> = arrayOfNulls(256)//デフォーマーのみのファイル対応

    private external fun initJNI(): Long
    private external fun destroyJNI(nativecontext: Long)
    private external fun setFbxStrJNI(nativecontext: Long, fbxStr: ByteArray)
    private external fun getNumMeshJNI(nativecontext: Long): Int
    private external fun getMeshPointerJNI(nativecontext: Long, meshIndex: Int): Long
    private external fun getNumNonMeshDeformerJNI(nativecontext: Long): Int
    private external fun getNonMeshDeformerPointerJNI(nativecontext: Long, defoIndex: Int): Long

    init {
        nativeContext = initJNI()
    }

    //最期に破棄する
    fun destroy() {
        destroyJNI(nativeContext)
    }

    fun setFbxFile(con: Context, rawId: Int): Boolean {
        val raw: InputStream = con.getResources().openRawResource(rawId)
        val fileStr = raw.readBytes()
        setFbxStrJNI(nativeContext, fileStr)
        NumMesh = getNumMeshJNI(nativeContext)
        Mesh = arrayOfNulls(NumMesh)
        for (i in 0 until NumMesh) {
            Mesh!![i] = FbxMeshNode(getMeshPointerJNI(nativeContext, i))
        }
        //Deformerのみのファイルの場合
        if (NumMesh == 0) {
            NumDeformer = getNumNonMeshDeformerJNI(nativeContext)
            for (i in 0 until NumDeformer) {
                deformer[i] = Deformer(getNonMeshDeformerPointerJNI(nativeContext, i))
            }
        }
        return true
    }

    fun getNumFbxMeshNode(): Int {
        return NumMesh
    }

    fun getFbxMeshNode(index: Int): FbxMeshNode? {
        return Mesh!![index]
    }

    fun getNumNoneMeshDeformer(): Int {
        return NumDeformer
    }

    fun getNoneMeshDeformer(index: Int): Deformer? {
        return deformer[index]
    }
}
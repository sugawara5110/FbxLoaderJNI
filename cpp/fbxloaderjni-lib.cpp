#include <jni.h>
#include "../../../../../FbxLoader/FbxLoader.h"

extern "C" {

static void inName(JNIEnv *env, jcharArray outName, char *inName) {
    if (!inName || !outName)return;
    //outNameのポインタを取得
    jchar *name = env->GetCharArrayElements(outName, 0);
    size_t len = strlen(inName);
    for (int i = 0; i < len; i++) {
        name[i] = (jchar) inName[i];//ポインタで代入
    }
    env->ReleaseCharArrayElements(outName, name, 0);//ポインタ解放
}

static void inIntArray(JNIEnv *env, jintArray outArr,int *inArr, int size) {
    if (!inArr || !outArr)return;
    jint *arr = env->GetIntArrayElements(outArr, 0);
    for (int i = 0; i < size; i++) {
        arr[i] = (jint) inArr[i];
    }
    env->ReleaseIntArrayElements(outArr, arr, 0);
}

static void inDoubleArray(JNIEnv *env,jdoubleArray outArr,double *inArr, int size) {
    if (!inArr || !outArr)return;
    jdouble *arr = env->GetDoubleArrayElements(outArr, 0);
    for (int i = 0; i < size; i++) {
        arr[i] = (jdouble) inArr[i];
    }
    env->ReleaseDoubleArrayElements(outArr, arr, 0);
}

static jint nameLen(char *name) {
    size_t ret = 0;
    if (name)ret = strlen(name);
    return (jint) ret;
}

//FbxLoader
JNIEXPORT jlong JNICALL
Java_jp_sugasato_fbxloaderjni_FbxLoader_initJNI(
        JNIEnv *env,  //VMのポインタ
        jobject thiz)//kotlin側FbxLoaderのポインタ
{
    FbxLoader *fbx = new FbxLoader();
    return (jlong) fbx;
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxLoader_destroyJNI(
        JNIEnv *env, jobject thiz,
        jlong nativeContext) {
    FbxLoader *fbx = (FbxLoader *) nativeContext;
    if (fbx == nullptr)return;
    delete fbx;
    fbx = nullptr;
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxLoader_setFbxStrJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext, //インスタンスアドレス値
        jbyteArray fbxStr)//fbxファイル内バイナリデータ
{
    //インスタンスアドレス値から保持インスタンス取得
    FbxLoader *fbx = (FbxLoader *) nativeContext;
    int len = env->GetArrayLength(fbxStr);
    char *buf = new char[len];
    env->GetByteArrayRegion(fbxStr, 0, len, reinterpret_cast<jbyte *>(buf));
    fbx->setBinaryInFbxFile(buf, len);
    delete[] buf;
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxLoader_getNumMeshJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext) {
    FbxLoader *fbx = (FbxLoader *) nativeContext;
    return (jint) fbx->getNumFbxMeshNode();
}

JNIEXPORT jlong JNICALL
Java_jp_sugasato_fbxloaderjni_FbxLoader_getMeshPointerJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint meshIndex)//ポインタを取得するメッシュのインデックス
{
    FbxLoader *fbx = (FbxLoader *) nativeContext;
    if (meshIndex >= fbx->getNumFbxMeshNode())return 0;
    return (jlong) fbx->getFbxMeshNode((unsigned int) meshIndex);
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxLoader_getNumNonMeshDeformerJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext) {
    FbxLoader *fbx = (FbxLoader *) nativeContext;
    return (jint) fbx->getNumNoneMeshDeformer();
}

JNIEXPORT jlong JNICALL
Java_jp_sugasato_fbxloaderjni_FbxLoader_getNonMeshDeformerPointerJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint defoIndex) {
    FbxLoader *fbx = (FbxLoader *) nativeContext;
    if (defoIndex >= fbx->getNumNoneMeshDeformer())return 0;
    return (jlong) fbx->getNoneMeshDeformer((unsigned int) defoIndex);
}

//FbxMeshNode
JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNameLengthJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return nameLen(mesh->getName());
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_GetNameJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jcharArray Name) {//Nameはkotlin側で生成
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inName(env, Name, mesh->getName());
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_GetNumVerticesJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jint) mesh->getNumVertices();
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_GetVerticesJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jdoubleArray inArr) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    //getNumVertices()は頂点数で1頂点3要素なので * 3
    inDoubleArray(env, inArr, mesh->getVertices(), mesh->getNumVertices() * 3);
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_GetNumPolygonVerticesJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jint) mesh->getNumPolygonVertices();
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_GetPolygonVerticesJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jintArray inArr) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inIntArray(env, inArr, mesh->getPolygonVertices(), mesh->getNumPolygonVertices());
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_GetNumPolygonJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jint) mesh->getNumPolygon();
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getPolygonSizeJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint pindex) {//ポリゴンインデックス
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jint) mesh->getPolygonSize((unsigned int) pindex);
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_GetNumMaterialJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jint) mesh->getNumMaterial();
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getMaterialNameLengthJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return nameLen(mesh->getMaterialName((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getMaterialNameJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jcharArray Name) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inName(env, Name, mesh->getMaterialName((unsigned int) layerIndex));
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getMaterialMappingInformationTypeLengthJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return nameLen(mesh->getMaterialMappingInformationType((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getMaterialMappingInformationTypeJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jcharArray Name) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inName(env, Name, mesh->getMaterialMappingInformationType((unsigned int) layerIndex));
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getMaterialNoOfPolygonJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint polygonNo,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jint) mesh->getMaterialNoOfPolygon((unsigned int) polygonNo, (unsigned int) layerIndex);
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getDiffuseTextureNameLengthJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return nameLen(mesh->getDiffuseTextureName((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getDiffuseTextureNameJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jcharArray Name) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inName(env, Name, mesh->getDiffuseTextureName((unsigned int) layerIndex));
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNormalTextureNameLengthJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return nameLen(mesh->getNormalTextureName((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNormalTextureNameJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jcharArray Name) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inName(env, Name, mesh->getNormalTextureName((unsigned int) layerIndex));
}

JNIEXPORT jdouble JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getDiffuseColorJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jint colIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jdouble) mesh->getDiffuseColor((unsigned int) layerIndex, (unsigned int) colIndex);
}

JNIEXPORT jdouble JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getSpecularColorJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jint colIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jdouble) mesh->getSpecularColor((unsigned int) layerIndex, (unsigned int) colIndex);
}

JNIEXPORT jdouble JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getAmbientColorJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jint colIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jdouble) mesh->getAmbientColor((unsigned int) layerIndex, (unsigned int) colIndex);
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNumNormalJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jint) mesh->getNumNormal((unsigned int) layerIndex);
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNormalNameLengthJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return nameLen(mesh->getNormalName((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNormalNameJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jcharArray Name) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inName(env, Name, mesh->getNormalName((unsigned int) layerIndex));
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNormalMappingInformationTypeLengthJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return nameLen(mesh->getNormalMappingInformationType((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNormalMappingInformationTypeJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jcharArray Name) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inName(env, Name, mesh->getNormalMappingInformationType((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNormalJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jdoubleArray inArr) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inDoubleArray(env, inArr,
                  mesh->getNormal((unsigned int) layerIndex),
                  mesh->getNumNormal((unsigned int) layerIndex));
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNumUVJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jint) mesh->getNumUV((unsigned int) layerIndex);
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getUVNameLengthJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return nameLen(mesh->getUVName((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getUVNameJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jcharArray Name) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inName(env, Name, mesh->getUVName((unsigned int) layerIndex));
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getUVMappingInformationTypeLengthJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return nameLen(mesh->getUVMappingInformationType((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getUVMappingInformationTypeJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jcharArray Name) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inName(env, Name, mesh->getUVMappingInformationType((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getUVJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jdoubleArray inArr) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inDoubleArray(env, inArr,
                  mesh->getUV((unsigned int) layerIndex),
                  mesh->getNumUV((unsigned int) layerIndex));
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNumUVindexJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jint) mesh->getNumUVindex((unsigned int) layerIndex);
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getUVindexJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jintArray inArr) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inIntArray(env, inArr,
               mesh->getUVindex((unsigned int) layerIndex),
               mesh->getNumUVindex((unsigned int) layerIndex));
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getAlignedUVJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint layerIndex,
        jdoubleArray inArr) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    inDoubleArray(env, inArr,
                  mesh->getAlignedUV((unsigned int) layerIndex),
                  mesh->getNumUVindex((unsigned int) layerIndex) * 2);
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getNumDeformerJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jint) mesh->getNumDeformer();
}

JNIEXPORT jlong JNICALL
Java_jp_sugasato_fbxloaderjni_FbxMeshNode_getDeformerPointerJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint defoIndex) {
    FbxMeshNode *mesh = (FbxMeshNode *) nativeContext;
    return (jlong) mesh->getDeformer((unsigned int) defoIndex);
}

//Deformer
JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_Deformer_getNameLengthJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext) {
    Deformer *defo = (Deformer *) nativeContext;
    return nameLen(defo->getName());
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_Deformer_getNameJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jcharArray Name) {
    Deformer *defo = (Deformer *) nativeContext;
    inName(env, Name, defo->getName());
}

JNIEXPORT jint JNICALL
Java_jp_sugasato_fbxloaderjni_Deformer_getIndicesCntJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext) {
    Deformer *defo = (Deformer *) nativeContext;
    return (jint) defo->getIndicesCount();
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_Deformer_GetIndicesJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jintArray inArr) {
    Deformer *defo = (Deformer *) nativeContext;
    inIntArray(env, inArr, defo->getIndices(), defo->getIndicesCount());
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_Deformer_GetWeightsJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jdoubleArray inArr) {
    Deformer *defo = (Deformer *) nativeContext;
    inDoubleArray(env, inArr, defo->getWeights(), defo->getIndicesCount());
}

JNIEXPORT jdouble JNICALL
Java_jp_sugasato_fbxloaderjni_Deformer_getTransformLinkMatrixJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint y,
        jint x) {
    Deformer *defo = (Deformer *) nativeContext;
    return (jdouble) defo->getTransformLinkMatrix((unsigned int) y, (unsigned int) x);
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_Deformer_EvaluateLocalTransformJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jlong time) {
    Deformer *defo = (Deformer *) nativeContext;
    defo->EvaluateLocalTransform(time);
}

JNIEXPORT void JNICALL
Java_jp_sugasato_fbxloaderjni_Deformer_EvaluateGlobalTransformJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jlong time) {
    Deformer *defo = (Deformer *) nativeContext;
    defo->EvaluateGlobalTransform(time);
}

JNIEXPORT jdouble JNICALL
Java_jp_sugasato_fbxloaderjni_Deformer_getEvaluateLocalTransformJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint y,
        jint x) {
    Deformer *defo = (Deformer *) nativeContext;
    return (jdouble) defo->getEvaluateLocalTransform((unsigned int) y, (unsigned int) x);
}

JNIEXPORT jdouble JNICALL
Java_jp_sugasato_fbxloaderjni_Deformer_getEvaluateGlobalTransformJNI(
        JNIEnv *env,
        jobject thiz,
        jlong nativeContext,
        jint y,
        jint x) {
    Deformer *defo = (Deformer *) nativeContext;
    return (jdouble) defo->getEvaluateGlobalTransform((unsigned int) y, (unsigned int) x);
}

}
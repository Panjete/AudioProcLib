#ifndef libaudioAPI_h__
#define libaudioAPI_h__

typedef struct{
    int label;
    float prob;
}pred_t;

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred);

#endif // libaudioAPI_h__



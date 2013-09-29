#include <Python.h>
#include <string.h>
void urldecode(char *p)
{
    register int i=0;
    while(*(p+i))
    {
        if ((*p=*(p+i)) == '%')
        {
            *p=*(p+i+1) >= 'A' ? ((*(p+i+1) & 0XDF) - 'A') + 10 : (*(p+i+1) - '0');
            *p=(*p) * 16;
            *p+=*(p+i+2) >= 'A' ? ((*(p+i+2) & 0XDF) - 'A') + 10 : (*(p+i+2) - '0');
            i+=2;
        }
        else if (*(p+i)=='+')
        {
            *p=' ';
        }
        p++;
    }
    *p='\0';
}
int str_startwith(const char *str, const char *reg) {  
    while (*str && *reg && *str == *reg) {  
        str ++;  
        reg ++;  
    }  
    if (!*reg) return 1;  
    return 0;  
}  
static PyObject* unquote(PyObject* self, PyObject* args)
{
    char *p;
    if (! PyArg_ParseTuple(args, "s", &p))
        return NULL;
    urldecode(p);
    return Py_BuildValue("s", p);
}
static PyObject* parseurl(PyObject* self, PyObject* args)
{
    char *p,*token;
    int len_token,len_key;
    if (! PyArg_ParseTuple(args, "s", &p))
        return NULL;
    PyObject *d = PyDict_New();
    PyObject *val;
    while ((token = strsep(&p, "&")))
    {
        len_token = strlen(token);
        char *key = strsep(&token,"=");
        len_key = strlen(key);
        if(len_key == len_token){
            continue;
        }
        val = Py_BuildValue("s", token);
        char *tmp = (char*)malloc((strlen(key)+5)*sizeof(char));
        sprintf(tmp,"%s",key);
        PyObject *k = Py_BuildValue("s", tmp);
        PyDict_SetItem(d, k, val);
        Py_XDECREF(k);
        Py_XDECREF(val);
        free(tmp);
        key = NULL;
        token = NULL;
    }
    p = NULL;
    return d;
}

static PyMethodDef unquoteMethods[] =
{
    {"unquote",  unquote, METH_VARARGS, "unquote url"},
    {"parseurl",  parseurl, METH_VARARGS, "parse url"},
    {NULL, NULL, 0, NULL}
};
PyMODINIT_FUNC initfastfunc(void)
{
    Py_InitModule("fastfunc", unquoteMethods);
}

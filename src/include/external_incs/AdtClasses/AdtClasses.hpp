#pragma once

#include <limits>
#include <iostream>
#include <vector>
#include <fstream>
#include <locale>
#include <codecvt>
#include <chrono>
#include <sstream>
#include <map>
#include <memory>
#include <stdexcept>
#include <functional>
#include <filesystem>
#include <MathLib/Random.hpp>
#include <MathLib/AddMath.hpp>
#include <MathLib/Vector4.hpp>
#include <list>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

using namespace std;
#define empty_lambda [](){;}

namespace adc{

const string _simbs = "?`~!@#$%^&*()_+=-,.<>/|\\[]{}?\"'";

typedef std::chrono::_V2::steady_clock::time_point chrono_tpoint_t;

template<class C, int N>
string str(array<C, N> arr){
	string o = "{";
	for(const C&el:arr){
		o += ' ' + to_string(el) + ",";
	}
	o.pop_back();
	o += "}";
	return {o};
}

void trimTrailingSpaces(std::string& str) {
    size_t endpos = str.find_last_not_of(" \t");
    if (endpos != std::string::npos) {
        str = str.substr(0, endpos + 1);
    } else {
        // Строка состоит только из пробелов
        str.clear();
    }
}

template<class K, class V>
V findKeyByValue(const map<K, V> &m, const V &value) {
    for (const auto &pair : m) {
        if (pair.second == value) {
            return pair.first;
        }
    }
    return {}; // If not found, return empty string
}

template<class K, class V>
bool isValueInMap(const map<K, V> &m, const V &value) {
    for (const auto &pair : m) {
        if (pair.second == value) {
            return true;
        }
    }
    return false; // If not found, return empty string
}

chrono_tpoint_t getChornoTimeNow(){
    return std::chrono::steady_clock::now();
}

float getChronoElapsed(chrono_tpoint_t begin){
    return std::chrono::duration_cast<std::chrono::milliseconds>(getChornoTimeNow() - begin).count();
}

bool instr(string str, char ch){
    for(const char&c:str){if(c==ch) return true;}
    return false;
}

bool is_fileexists(string path){
    return filesystem::exists(path);
}

template<class K, class V>
bool isKeyInMap(map<K, V> &mp, K &elem){
    return mp.find(elem) != mp.end();
}

string getTime(){
    auto now = chrono::system_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;
    time_t now_c = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_c);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", now_tm);
    stringstream ss;
    ss << buffer << "." << setfill('0') << setw(3) << ms.count();
    return ss.str();
}

time_t getTimeT(){
    return chrono::system_clock::to_time_t(chrono::system_clock::now());
}

wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

void enbaleUTF16(){
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT); 
    SetConsoleOutputCP(65001);
}

wstring stringToWstring(string src){
    return converter.from_bytes(src);
}

string wstringToString(wstring src){
    return converter.to_bytes(src);
}

bool stob(string str){
    return str == "true";
}

string to_stringb(bool b){
    if(b) return "True";
    return "False";
}

std::string pixel(eml::vec3f r){
    std::stringstream ss;
    ss << "\033[48;2;" << abs(adm::clamp(0, 255, round(r.x))) << ";" << abs(adm::clamp(0, 255, round(r.y))) <<";" << abs(adm::clamp(0, 255, round(r.z))) <<"m "<<"\033[0;0m";
    return ss.str();
}

std::wstring wpixel(eml::vec3f r){
    std::wstringstream ss;
    ss << L"\033[48;2;" << abs(adm::clamp(0, 255, round(r.x))) << L";" << abs(adm::clamp(0, 255, round(r.y))) << L";" << abs(adm::clamp(0, 255, round(r.z))) <<L"m "<<L"\033[0;0m";
    return ss.str();
}

std::string rgbBGChar(eml::vec3f r, char c){
    std::stringstream ss;
    ss << "\033[48;2;" << abs(adm::clamp(0, 255, round(r.x))) << ";" << abs(adm::clamp(0, 255, round(r.y))) <<";" << abs(adm::clamp(0, 255, round(r.z))) <<"m"<<c<<"\033[0;0m";
    return ss.str();
}

std::string rgbFRChar(eml::vec3f r, char c){
    std::stringstream ss;
    ss << "\033[38;2;" << abs(adm::clamp(0, 255, round(r.x))) << ";" << abs(adm::clamp(0, 255, round(r.y))) <<";" << abs(adm::clamp(0, 255, round(r.z))) <<"m"<<c<<"\033[0;0m";
    return ss.str();
}

std::wstring wrgbFRChar(eml::vec3f r, wchar_t c){
    std::wstringstream ss;
    ss << L"\033[38;2;" << abs(adm::clamp(0, 255, round(r.x))) << L";" << abs(adm::clamp(0, 255, round(r.y))) << L";" << abs(adm::clamp(0, 255, round(r.z))) << L"m" << c << L"\033[0;0m";
    return ss.str();
}

std::wstring wrgbBGChar(eml::vec3f r, wchar_t c){
    std::wstringstream ss;
    ss << L"\033[48;2;" << abs(adm::clamp(0, 255, round(r.x))) << L";" << abs(adm::clamp(0, 255, round(r.y))) << L";" << abs(adm::clamp(0, 255, round(r.z))) << L"m" << c << L"\033[0;0m";
    return ss.str();
}

std::string rgbFRString(eml::vec3f r, string st){
    std::stringstream ss;
    ss << "\033[38;2;" << abs(adm::clamp(0, 255, round(r.x))) << ";" << abs(adm::clamp(0, 255, round(r.y))) << ";" << abs(adm::clamp(0, 255, round(r.z))) << "m" << st << "\033[0;0m";
    return ss.str();
}

std::wstring wrgbFRString(eml::vec3f r, wstring st){
    std::wstringstream ss;
    ss << L"\033[38;2;" << abs(adm::clamp(0, 255, round(r.x))) << L";" << abs(adm::clamp(0, 255, round(r.y))) << L";" << abs(adm::clamp(0, 255, round(r.z))) << L"m" << st << L"\033[0;0m";
    return ss.str();
}

std::wstring wrgbBGString(eml::vec3f r, wstring st){
    std::wstringstream ss;
    ss << L"\033[48;2;" << abs(adm::clamp(0, 255, round(r.x))) << L";" << abs(adm::clamp(0, 255, round(r.y))) << L";" << abs(adm::clamp(0, 255, round(r.z))) << L"m" << st << L"\033[0;0m";
    return ss.str();
}

std::wstring wrgbBGFRChar(eml::vec3f bg, eml::vec3f fr, wchar_t c){
    return wrgbBGString(bg, wrgbFRChar(fr, c));
}

std::wstring wrgbBGFRString(eml::vec3f bg, eml::vec3f fr, wstring s){
    return wrgbBGString(bg, wrgbFRString(fr, s));
}



string to_string(char ch){
    string o;o+=ch;
    return {o};
}

wstring to_wstring(wchar_t ch){
    wstring o;o+=ch;
    return {o};
}

bool replaceFirst(std::string& str, std::string from, std::string to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

bool replaceFirstW(std::wstring& str, std::wstring from, std::wstring to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void replaceAll(std::string& str, std::string from, std::string to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void replaceAllw(std::wstring& str, std::wstring from, std::wstring to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void replaceVInterSpaces(vector<string> &a, string interspace = " ", string toReplace = ""){for(string &elem : a){replaceAll(elem, interspace, toReplace);}}
void replaceInterSpaces(string &a, string interspace = " ", string toReplace = ""){replaceAll(a, interspace, toReplace);}
void replaceVInterSpacesW(vector<wstring> &a, wstring interspace = L" ", wstring toReplace = L""){for(wstring &elem : a){replaceAllw(elem, interspace, toReplace);}}
void replaceInterSpacesW(wstring &a, wstring interspace = L" ", wstring toReplace = L""){replaceAllw(a, interspace, toReplace);}

template<class TString>
TString repeat(TString part, int num){
    TString out;for(int i = 0; i < num; i++){out += part;}
    return {out};
}

/*
aInd - first indx;
bInd - second indx;
    bInd not changed? - return all str before aInd
    bInd <= 0 - return str from aInd, to strsize + bInd (bInd = 0 => return from aInd to end)
    bInd > 0 - return str from aInd, bInd simbols
*/
template<class TString> 
TString slice(TString str, int aInd = 0, int bInd = INT_MAX){
    if(bInd == INT_MAX) {return str.substr(aInd);}
    else if(bInd <= 0) {return str.substr(aInd, str.size()-1+bInd);}
    else {return str.substr(aInd, bInd);}
}

template<class TString> 
TString clamp(TString str, int bInd = -1){
    if(bInd == -1 || bInd >= str.size()) return str;
    return TString(str, 0, bInd);
}

template<class c>
void print(c cc, bool needEnd = true){needEnd ? cout<<cc<<endl : cout<<cc<<' ';}

template<class kc>
bool in(vector<kc> v, kc i){
    for(kc k : v){
        if(k == i){
            return true;
        }
    }
    return false;
}

template<class vc>
int index(const vector<vc> &vecs, vc key, int start_index = 0){
    for(int i = start_index; i < vecs.size(); i++){
        if(vecs[i] == key) return i;
    }
    return -1;
}

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args){
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0)
    {
        throw std::runtime_error("Error during formatting.");
    }

    vector<int> x{0,1};

    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf(new char[ size ]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

struct BoolWRP{
    bool val;
};

template<class kc, class vc>
class dict{
    public:
    std::vector<kc> keys;
    std::vector<vc> values;
    dict(){
        ;
    }

    int size(){
        return values.size();
    }

    void set(kc key, vc val){
        if(in(keys, key)){
            values.at(index(keys, key)) = val;
        } else {
            keys.push_back(key);
            values.push_back(val);
        }
    }

    bool in_key(kc key){
        return in(keys, key);
    }

    bool in_val(vc val){
        return in(values, val);
    }

    vc &get(kc key){
        return values[index(keys, key)];
    }

    vc &operator[](kc key){
        if(!in(keys, key)) set(key, vc());
        return values[index(keys, key)];
    }
};

template<class kc, class vc>
class paar{
    public:
    kc key;
    vc value;
    vc *vpointer;
    bool nvalue = false;

    paar(){}

    paar(kc k, vc v){
        key=k;
        value=v;
        vpointer = &value;
    }

    void setv(vc val){
        value=val;
        vpointer = &value;
    }

    void setk(kc key_){
        key=key_;
    }

    vc &get(){
        return value;
    }

    vc *getPointer(){
        return vpointer;
    }

    void print(){
        cout<<"key="<<key<<" | value="<<value<<endl;
    }

    bool operator==(paar<kc, vc> &other){
        return key==other.key && value==other.value;
    }
};

class custom_exception : std::exception {
    private:
    std::string what_message;

    public:
    custom_exception(std::string msg) : what_message(msg) {}

    const char* what(){
        return what_message.c_str();
    }
};

template<class alpha>
class Ideoma{
    public:
    
    alpha a, b;
    
    Ideoma(alpha a_, alpha b_){
        a = a_;
        b = b_;
    }

    Ideoma(){
        a = alpha();
        b = alpha();
    }
};

template<class kc, class vc>
paar<kc, vc> &getPaarByName(vector<paar<kc, vc>> vd, kc name){
    for(paar<kc, vc> &p : vd){
        if(p.key == name){
            return p;
        }
    }
    cout<<"NPOS: "<<name<<endl;
    //return npos
}

template<class kc, class vc>
int paarIndex(vector<paar<kc, vc>> vd, paar<kc, vc> paar){
    for(int i = 0; i < vd.size(); i++){
        if(vd[i] == paar){
            return i;
        }
    }
    return -1;
}

template<class kc, class vc>
int paarIndexByName(vector<paar<kc, vc>> vd, kc name){
    for(int i = 0; i < vd.size(); i++){
        if(vd[i].key == name){
            return i;
        }
    }
    return -1;
}

template<class kc, class vc>
bool keyInPaars(vector<paar<kc, vc>> paars, kc key){
    for(paar<kc, vc> p : paars){
        if(p.key == key){
            return true;
        }
    }
    return false;
}

template<class f, class s>
vector<f> getKeysVPairs(vector<pair<f,s>> vc){
    vector<f> o; for(pair<f,s> &el : vc){o.push_back(el.first);}
    return {o};
}

template<class kc, class vc>
vector<reference_wrapper<vc>> getOnlyVals(vector<paar<kc, vc>> vd){
    vector<reference_wrapper<vc>> vals;
    for(paar<kc, vc> p : vd){
        vals.push_back(reference_wrapper<vc>(p.value));
    }
    return {vals};
}

template<class k>
k &getLast(vector<k> v){
    return v[v.size()-1];
}

template<class k>
vector<k> merge(vector<k> to, const vector<k> &from){
    for(const k&el: from){
        to.push_back(el);
    }
    return to;
}

template<class cs>
void printv(vector<cs> vs, bool qoutes = false, char end=' '){
    for(cs s: vs){
        if(qoutes) cout<<"'"<<s<<"'"<<end;
        else cout<<s<<end;
    }
    cout<<endl;
}

vector<string> getFileLines(std::string fileName, char sep = '\n'){
    ifstream ogfile(fileName);
    if(!ogfile.is_open()){
        cerr<<"[ERROR] getFileLines: cant open file\n";
    }
    string line;
    vector<string> lines;
    while (!ogfile.eof()){
        getline(ogfile,line, sep);
        if(line.size()>=1)lines.push_back(line);
    }

    return {lines};
}

vector<wstring> getFileLinesW(std::string fileName, wchar_t sep = L'\n'){
    wifstream ogfile(fileName);
    if(!ogfile.is_open()){
        cerr<<"[ERROR] getFileLinesW: cant open file\n";
    }
    wstring line;
    vector<wstring> lines;
    while (!ogfile.eof()){
        getline(ogfile,line, sep);
        if(line.size()>=1)lines.push_back(line);
    }

    return {lines};
}

template<class T>
void writeToFile(string fileName, vector<T> lines, char mode = 'w', char sep = '\n'){
    switch (mode){
        case 'w':{
            std::ofstream out(fileName);
            if(out.is_open()){
                for(T &el :lines){
                    out << el << sep;
                }
            } else {
                cerr<<"[ERROR] writeToFile (mode=w): cant open file\n";
            }
            out.close();
            break;
        };
        case 'a':{
            std::ofstream out(fileName, ios::app);
            if(out.is_open()){
                for(T &el :lines){
                    out << el << sep;
                }
            } else {
                cerr<<"[ERROR] writeToFile (mode=a): cant open file\n";
            }
            out.close();
            break;
        };
    }
}


void writeToFileW(string fileName, vector<wstring> lines, char mode = 'w', wchar_t sep = L'\n', wstring end = L"\n"){
    switch (mode){
        case 'w':{
            std::wofstream out(fileName);
            if(out.is_open()){
                for(wstring &el :lines){
                    out << el << sep;
                }
                out<<end;
            } else {
                cerr<<"[ERROR] writeToFile (mode=w): cant open file\n";
            }
            out.close();
            break;
        };
        case 'a':{
            std::wofstream out(fileName, ios::app);
            if(out.is_open()){
                for(wstring &el :lines){
                    out << el << sep;
                }
                out<<end;
            } else {
                cerr<<"[ERROR] writeToFile (mode=a): cant open file\n";
            }
            out.close();
            break;
        };
    }
}

template<class T>
void printtf(vector<T> x, std::string fileName, char sep = ' ', char end = '\n'){
    std::ofstream out(fileName, ios::app);
    if(out.is_open()){
        for(T &el :x){
            out << el << sep;
        }
        out<<end;
    } else {
        cerr<<"[ERROR] printtf: cant open file\n";
    }
    out.close();
}

template<class T>
vector<T> delElems(vector<T> vc, int ind){
    
}

vector<int> toIntAll(vector<string> vc){
    vector<int> o;for(string &el : vc){o.push_back(::stoi(el));}
    return {o};
}

vector<string> split(string line, char delim = ' '){
    if(line.find(delim) != string::npos){
        vector<string> elems{""};
        bool isSpace = true;
        
        for(char ch : line){
            if(isSpace && ch!=delim || !isSpace && ch!=delim){
                elems[elems.size()-1]+=ch;
            }
            isSpace = ch == delim;
            if (isSpace) elems.push_back("");
        }

        return {elems};
    }

    return {line};
}

vector<string> ssplit(string line, char delim = ' '){
    if(line.find(delim) != string::npos){
        vector<string> elems{""};
        bool isSpace = true;
        
        for(char ch : line){
            if((isSpace && ch!=delim || !isSpace && ch!=delim) && !instr(_simbs, ch)){
                elems[elems.size()-1]+=ch;
            } else if(instr(_simbs, ch)){
                elems.push_back(to_string(ch));
            }
            isSpace = (ch == delim) || instr(_simbs, ch);
            if (isSpace) elems.push_back("");
        }

        return {elems};
    }

    return {line};
}

vector<string> outEmptys(vector<string> vc){
    vector<string> ovc;
    for(string&str:vc){
        if(!str.empty()){
            ovc.push_back(str);
        }
    }
    return {ovc};
} 

template<class T>
vector<vector<T>> splitVec(vector<T> vc, T elemSep){
    vector<vector<T>> out;
    bool appending = false;
    for(T &el : vc){
        if(el == elemSep){
            out.push_back(vector<T>());
            appending = true;
        } else if(appending){
            out.back().push_back(el);
        }
    }
    return {out};
}

/* 
inda - start index
indb - end index
if indb <= 0 - return vector from inda to vsize+indb (indb = 0 => return all vector from inda)
if indb >  0 - return vector from inda to indb
*/
template<class T>
vector<T> sliceVec(vector<T> vc, int inda, int indb){
    return vector<T>(vc.begin() + inda, 
                     (indb <= 0) ? 
                        (vc.end() + indb) : 
                        (indb <= vc.size() ? 
                            (vc.begin() + indb) : 
                            (vc.end())
                        )
                    );
}

vector<wstring> wsplit(wstring line, wchar_t delim = L' '){
    if(line.find(delim) != wstring::npos){
        vector<wstring> elems{L""};
        bool isSpace = true;
        
        for(wchar_t ch : line){
            if(isSpace && ch!=delim || !isSpace && ch!=delim){
                elems[elems.size()-1]+=ch;
            }
            isSpace = ch == delim;
            if (isSpace) elems.push_back(L"");
        }

        return {elems};
    }

    return {line};
}


string join(vector<string> vs, char udel = ' '){
    string o;
    int inx=0;
    for(string s : vs){
        o+=s;
        if(inx!=vs.size()-1) o+=udel;
        inx++;
    }

    return {o};
}

string remove(string str, vector<char> vchs){
    string out;
    for(char ch : str){
        if(!in(vchs, ch)){
            out+=ch;
        }
    }
    return {out};
}

bool isInteger(std::string s){
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
   char * p;
   strtol(s.c_str(), &p, 10);
   return (*p == 0);
}

bool isFloat(std::string s){
    std::istringstream iss(s);
    float f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();
}

int getIndexCStr(const char* cstr, const char dst, int str_size){
    for(int i = 0; i < str_size; i++){if(cstr[i]==dst) {return i;}}
    return -1;
}

int getIndexStr(string str, char dst){
    for(int i = 0; i < str.size(); i++){if(str[i]==dst) {return i;}}
    return -1;
}

template <typename T>
void unpackVariadicTemplate(std::vector<T>& result) {}

template <typename T, typename... Args>
void unpackVariadicTemplate(std::vector<T>& result, T arg, Args... args) {
    result.push_back(arg);
    unpackVariadicTemplate(result, std::forward<Args>(args)...); 
}

template <typename T, typename... Args>
std::vector<T> unpack_args(T arg, Args... args){
    std::vector<T> out;
    unpackVariadicTemplate(out, arg, args...);
    return {out};
}

template<class T, class... ars>
int minIndx(T el, ars... es){
    auto tmpv = unpack_args(el, es...);
    int inx = 0, imin = tmpv[0];
    for(int i = 1; i < tmpv.size(); i++){
        if(tmpv[i] < imin) {
            imin = tmpv[i];
            inx = i;
        } 
    }
    return {inx};
    //minIndx(0, 1, 2); -> 0
    //minIndx(100, 45, 51, 90) -> 1
}

template<class T, class... ars>
bool isFirstEqualsAllOthers(T el, ars... es){
    auto tmpv = unpack_args(el, es...);
    for(T& _el: sliceVec(tmpv, 1, 0)){
        if(tmpv[0] != _el) return false;
    }
    return true;
}

template<class T, class... ars>
bool isFirstEqualsAnyOthers(T el, ars... es){
    auto tmpv = unpack_args(el, es...);
    for(T& _el: sliceVec(tmpv, 1, 0)){
        if(tmpv[0] == _el) return true;
    }
    return false;
}

template<class T>
bool isFirstEqualsAnyOthersV(T el, vector<T> es){
    for(T& _el: es){
        if(el == _el) return true;
    }
    return false;
}

template<class T, class... ars>
int isAnyEquals(T el, ars... es){
    vector<T> tmpv = unpack_args(el, es...);
    for(int i = 0; i < tmpv.size(); i++){
        vector<T> tm;
        for(int y = 0; y < tmpv.size(); y++){ if(y != i){ tm.push_back(tmpv[i]); }}
        if(isFirstEqualsAnyOthersV(tmpv[i], tm))
            return i;
    }
    return -1;
}

vector<int> range(int rng, int b = -1){
    vector<int> o;
    if(b==rng){return {};}
    if(b == -1){
        o.resize(rng);
        for(int i = 0; i < rng; i++){
            o[i] = i;
        }
    } else if( b >= 0 && b < rng){
        o.resize(rng);
        for(int i = rng, j = 0; i >= b; i--, j++){
            o[j] = i;
        }
    } else if(b > rng){
        o.resize(b);
        for(int i = rng; i < rng + b; i++){
            o[i-rng] = i;
        }
    }
    return {o};
}

template<class R, class T>
pair<R, T> choice_map(map<R, T> mp){
    vector<pair<R, T>> vc;
    for(auto &pt : mp){
        vc.push_back(pt);
    }
    return choice(vc);
}

template<class T>
T vsum(vector<T> vc){
    T vv = (T)0;
    for(const T& el:vc){
        vv += el;
    }
    return {vv};
}

template<class T, class R>
vector<R> vprocess(vector<T> vc, function<R(T)> func){
    vector<R> ovc;
    for(T&el:vc){
        ovc.push_back(func(el));
    }
    return {ovc};
}

template<class T, class... Args>
void printm(vector<vector<T>> m, Args... args){
    for(auto &l:m){
        printv(l, args...);
    }
    cout<<"-\n";
}

template<class T>
int count(const vector<T> &vc, const T el){
    int out = 0; for(const T&el_:vc){
        if(el==el_) out++;
    }
    return {out};
}

vector<int> getVectorWithVals(int vsize, int val){
    vector<int> o;
    for(int i:adc::range(vsize)){
        o.push_back(val);
    }
    return {o};
}

template<class T>
vector<T> vcopy(vector<T> &x){
    vector<T> to;
    for(T el: x){
        to.push_back(el);
    }
    return {to};
}

template<class T>
void vcopyto(vector<T> &to, vector<T> from){
    to.clear();
    for(T el: from){
        to.push_back(el);
    }
}

template<class T, class K>
vector<T> getKeys(map<T, K> mp_dict){
    vector<T> o; for(const auto&el:mp_dict){
        o.push_back(el.first);
    }
    return {o};
}

template<class T, class K>
vector<K> getVals(map<T, K> mp_dict){
    vector<K> o; for(const auto& el:mp_dict){
        o.push_back(el.second);
    }
    return {o};
}

template<class K, class V>
map<K, V> sortMapByKey(map<K, V> mp){
    map<K, V> out;
    vector<K> keys = getKeys(mp);

    sort(keys.begin(), keys.end());
    reverse(keys.begin(), keys.end());

    for(const K&el:keys){
        out[el] = mp[el];
    }

    return {out};
}

vector<float> allToFloat(vector<string> lines){
    return vprocess<string, float>(lines, [](const string& s){return stof(s); });
}

vector<double> allToDouble(vector<string> lines){
    return vprocess<string, double>(lines, [](const string& s){return stod(s); });
}

template<class T>
class queue{
    vector<T> vec;
    public:
    
    void push(T el){ vec.push_back(el); }
    T pop(){T el = vec.back(); vec.pop_back(); return {el}; }
    T &peek(){return vec.back();}
    bool isEmpty(){return vec.size()==0;}

    int size(){return vec.size();}

    queue(vector<T> vec): vec(vec){;}
    queue(){;}
};

void clearFile(string fileName){
    ofstream ofs(fileName);
    ofs<<'\n';
    ofs.close();
}

void pause(string msg = ""){
    cout<<msg<<endl;
    char ch;cin>>ch;
}

eml::vec3f vectorToV3(const vector<float> &vc){
    return {vc[0], vc[1], vc[2]};
}

eml::vec4f vectorToV4(const vector<float> &vc){
    return {vc[0], vc[1], vc[2], vc[3]};
}

vector<float> v3ToVector(const eml::vec3f &vc){
    return {vc.x, vc.y, vc.z};
}

vector<float> v4ToVector(const eml::vec4f &vc){
    return {vc.x, vc.y, vc.z, vc.w};
}

template<class T>
void vtmcopy(T *dst, const std::vector<T>& src) {
    dst = new T[src.size()];
    for (size_t i = 0; i < src.size(); i++) {
        dst[i] = src[i];
    }
}

template<class T, class R>
vector<R> processVector(vector<T> vec, function<R(int, T)> procr){
    vector<R> out; int inx = 0; for(T&el:vec){
        out.push_back(procr(inx, el));
        inx++;
    }
    return out; 
}

}
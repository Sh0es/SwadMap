#ifndef SWADMAP_H
#define SWADMAP_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Translation
{
// Data
	string word; //Base word that's translated
	string lang; //Translation language
	string tran; //Actual translation
	
public:
// Mutators
	void setLang(const string& s);
	void setWord(const string& s);
	void setTran(const string& s);

// Accessors
	string getWord() const;
	string getLang() const;
	string getTran() const;

// Operator Overloads
	Translation& operator =(const Translation& t);
	Translation& operator =(const string f[3]);

// Constructors
	Translation();
	Translation(const Translation& copy);
	Translation(string w);
	Translation(string feed[3]);
	~Translation();
};

class Translist
{
// Data
	string engWord;
	vector<string> translations;

public:
// Mutators
	void add(string wrd, int p);
	void remove(string wrd);
	
// Accessors
	string get(int p) const;
	string getEngWord() const;

// Constructors
	Translist();
	Translist(const Translist& copy);
	Translist(string w);
	~Translist();
};

class Swadmap
{
// Data
	vector<string> langs; //For sorting Translists
	vector<Translist> map;

// Private methods
	int posL(string s) const; //Position of language in `langs`
	int posM(string s) const; //Depth of translation in map

public:
// Mutators
	void add(string wd, string lg, string tn);
	void remove(string wd, string lg);
	
// Accessors
	string get(string& wd, string& lg) const;
	vector<string> getLangs() const;
	vector<Translist> getMap() const;
	vector<string>& getLangs();
	vector<Translist>& getMap();
	
// Constructors
	Swadmap();
	Swadmap(const Swadmap& copy);
	Swadmap(Swadmap&& move);
	Swadmap(vector<string>& l, vector<Translist>& m);
	Swadmap(string wd, string lg, string tn);
	~Swadmap();
};
#endif	// SWADMAP_H

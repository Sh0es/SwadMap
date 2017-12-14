#include <iostream>
#include <vector>
#include <string>
#include "swadMap.h"

using namespace std;

/*
 * Translation
 */

/* Mutators */

void Translation::setLang(const string& s)
{
	lang = s;
}

void Translation::setWord(const string& s)
{
	word = s;
}

void Translation::setTran(const string& s)
{
	tran = s;
}

/* Accessors */

string Translation::getWord() const
{
	return word;
}

string Translation::getLang() const
{
	return lang;
}

string Translation::getTran() const
{
	return tran;
}

/* Operator Overloads */

Translation& Translation::operator =(const Translation& t)
{
	word = t.getWord();
	lang = t.getLang();
	tran = t.getTran();

	return *this;
}

Translation& Translation::operator =(const string f[3])
{
	word = f[0];
	lang = f[1];
	tran = f[2];
	
	return *this;
}

/* Constructors */

Translation::Translation()
{
	word = string();
}

Translation::Translation(const Translation& copy)
{
	word = copy.getWord();
	lang = copy.getLang();
	tran = copy.getTran();
}

Translation::Translation(string w)
{
	word = w;
}

Translation::Translation(string feed[3])
{
	word = feed[0];
	lang = feed[1];
	tran = feed[2];
}

Translation::~Translation()
{}

/*
 * Translist
 */

/* Mutators */

void Translist::add(string wrd, int p)
{
	if(p < translations.size())
	{ translations.assign(p, wrd); }
	else if(p == translations.size())
	{ translations.push_back(wrd); }
	else
	{ cerr << "ERROR: Translist ADD position out of bounds." << endl; }
}

void Translist::remove(string wrd)
{
	int p = translations.size();

	for(int i = 0; i < translations.size(); i++)
	{
		if(translations.at(i) == wrd) 
		{
			p = i;
			break;
		}
	}
	if(p < translations.size()) 
	{ translations.erase(translations.begin() + p); }
	else 
	{ cerr << "ERROR: Language not found." << endl; }
}

/* Accessors */

string Translist::getEngWord() const
{
	return engWord;
}

string Translist::get(int p) const
{
	return translations.at(p);
}

/* Constructors */

Translist::Translist()
{
	engWord = string();
	translations = vector<string>();
}

Translist::Translist(const Translist& copy)
{
	engWord = copy.getEngWord();
	translations = vector<string>();

	for(int i = 0; i < translations.size(); i++)
	{ translations.at(i) = copy.get(i); }
}

Translist::Translist(string w)
{
	engWord = w;
}

Translist::~Translist()
{}

/*
 * Swadmap
 */

/* Private Methods */

int Swadmap::posL(string s) const
{
	int p = langs.size();

	for(int i = 0; i < langs.size(); i++)
	{
		if(langs.at(i) == s)
		{ p = i; }
	}
	return p;
}

int Swadmap::posM(string s) const
{
	int p = map.size();

	for(int i = 0; i < map.size(); i++)
	{
		if(map.at(i).getEngWord() == s)
		{ p = i; }
	}
	return p;
}

/* Mutators */

void Swadmap::add(string wd, string lg, string tn)
{
	int b = posL(lg);
	int d = posM(wd);
	if(b == langs.size())
	{ langs.push_back(lg); }
	if(d == map.size())
	{ map.push_back(Translist(wd)); }
	
	map.at(d).add(tn, b);
}

void Swadmap::remove(string wd, string lg)
{
	int d = posM(wd);
	
	if(d == langs.size())
	{ cerr << "ERROR: Search word not found." << endl; }
	else
	{ map.at(d).remove(wd); }
}

/* Accessors */

string Swadmap::get(string& wd, string& lg) const
{
	int mp = posM(wd);
	int lp = posL(lg);
	
	return map.at(mp).get(lp);
}

vector<string> Swadmap::getLangs() const
{
	return langs;
}

vector<Translist> Swadmap::getMap() const
{
	return map;
}

vector<string>& Swadmap::getLangs()
{
	return langs;
}

vector<Translist>& Swadmap::getMap()
{
	return map;
}

/* Constructors */

Swadmap::Swadmap()
{
	langs = vector<string>();
	map = vector<Translist>();
}

Swadmap::Swadmap(const Swadmap& copy)
{
	langs = copy.getLangs();
	map = copy.getMap();
}

Swadmap::Swadmap(Swadmap&& move)
{
	langs = vector<string>();
	map = vector<Translist>();
	langs = move.getLangs();
	map = move.getMap();
}

Swadmap::Swadmap(vector<string>& l, vector<Translist>& m)
{
	langs = l;
	map = m;
}

Swadmap::Swadmap(string wd, string lg, string tn)
{
	langs = vector<string>();
	map = vector<Translist>();
	add(wd, lg, tn);
}

Swadmap::~Swadmap()
{}
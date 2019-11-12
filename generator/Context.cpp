#include "Context.h"
#include "Options.h"
#include <stdio.h>

Context gContext;

Context::Context():
lineno_(1)
{}

Context::~Context()
{
	// ɾ�����е�definitionʵ��.
	for(size_t i = 0; i < definitions_.size(); i++)
		delete definitions_[i];
}

Definition* Context::findDefinition(const std::string& name)
{
	for(size_t i = 0; i < definitions_.size(); i++)
	{
		if(definitions_[i]->name_ == name)
			return definitions_[i];
	}

	return NULL;
}

int yyparse();
extern FILE *yyin;

bool Context::build()
{
	// ��Դ�ļ�.
	yyin = fopen(gOptions.input_.c_str(), "r");
	if(yyin == NULL)
	{
		fprintf(stderr, "failed to open file \"%s\".", gOptions.input_.c_str());
		return false;
	}

	// ���õ�ǰ�ļ���
	curFilename_ = gOptions.inputFN_;

	// ��ʼ�����ļ�.
	if(yyparse())
	{
		fclose(yyin);
		return false;
	}
	fclose(yyin);
	return true;
}

#include <cstdio>
#include <cstdarg>
#define GET_VARARGS(str, len, fmt) char str[len];va_list argptr;	va_start(argptr, fmt);vsprintf(str, fmt, argptr);va_end(argptr);
void Context::error(const char* e, ...)
{
	GET_VARARGS(str, 1024, e);
	fprintf(stderr, "%s(%d):%s\n", curFilename_.c_str(), lineno_, str);
}
#pragma once
#include <onmt/Tokenizer.h>

#if defined _WIN32 || defined _WIN64
#define TRANSLATE_EXPORT __declspec(dllexport)
#elif defined __linux__
#define TRANSLATE_EXPORT __attribute__((visibility("default")))
#else
#define TRANSLATE_EXPORT
#endif

extern "C" {

	TRANSLATE_EXPORT int Init(char* model_path, char* input_locale, char* output_locale);
	TRANSLATE_EXPORT int Translate(char* input, char* output);

}

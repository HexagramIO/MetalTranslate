#include "Translate.h"

#include <ctranslate2/translator_pool.h>
#include <iostream>
#include <onmt/Tokenizer.h>

extern "C" {

	onmt::Tokenizer* tokenizer;
	ctranslate2::TranslatorPool* translator;

	std::string in_locale;
	std::string out_locale;

	int Init(char* model_path, char* input_locale, char* output_locale) {

		std::string model_path_string(model_path);
		tokenizer = new onmt::Tokenizer(model_path_string + "sentencepiece.model");

		in_locale = std::string(input_locale);
		out_locale = std::string(output_locale);

		// CTranslate2
		const size_t num_translators = 1;
		auto time_2 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "2 " << std::ctime(&time_2) << std::endl;
		const size_t num_threads_per_translator = 8; // Unused with DNNL
		translator = new ctranslate2::TranslatorPool(
				num_translators, num_threads_per_translator,
				model_path_string + "model", ctranslate2::Device::CPU);

		return 0;
	}

	int Translate(char *input, char *output) {

		std::string input_string(input);

		std::vector <std::string> tokens;
		tokenizer->tokenize(input_string, tokens);

		std::string source_prefix = "__" + in_locale + "__";
		tokens.insert(tokens.begin(), source_prefix);

		const std::vector <std::vector<std::string>> batch = {tokens};
		const std::vector <std::vector<std::string>> target_prefix = {
				{"__" + out_locale + "__"}};
		const int max_batch_size = 2024;

		const std::vector <ctranslate2::TranslationResult> results =
				translator->translate_batch(batch, target_prefix);

		const std::vector <std::string> translatedTokens = results[0].output();

		std::string result = tokenizer->detokenize(translatedTokens);

		// Remove target prefix
		// __es__ Traducción de texto con MetalTranslate
		// -> Traducción de texto con MetalTranslate
		result = result.substr(7);
		strcpy(output, result.c_str());

		return 0;

	}
}
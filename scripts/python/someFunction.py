import random
import nltk
import json

# Set the NLTK data path
nltk.data.path.append('.')

def split_to_sentences(data):
    sentences = data.split('\n')
    sentences = [s.strip() for s in sentences]
    sentences = [s for s in sentences if len(s) > 0]
    return sentences

def tokenize_sentences(sentences):
    tokenized_sentences = []
    for sentence in sentences:
        sentence = sentence.lower()
        tokenized = nltk.word_tokenize(sentence)
        tokenized_sentences.append(tokenized)
    return tokenized_sentences

def get_tokenized_data(data):
    sentences = split_to_sentences(data)
    tokenized_sentences = tokenize_sentences(sentences)
    return tokenized_sentences

def count_words(tokenized_sentences):
    word_counts = {}
    for sentence in tokenized_sentences:
        for token in sentence:
            word_counts[token] = word_counts.get(token, 0) + 1
    return word_counts

def get_words_with_nplus_frequency(tokenized_sentences, count_threshold):
    closed_vocab = []
    word_counts = count_words(tokenized_sentences)
    for word, cnt in word_counts.items():
        if cnt >= count_threshold:
            closed_vocab.append(word)
    return closed_vocab

def replace_oov_words_by_unk(tokenized_sentences, vocabulary, unknown_token="<unk>"):
    vocabulary = set(vocabulary)
    replaced_tokenized_sentences = []
    for sentence in tokenized_sentences:
        replaced_sentence = [token if token in vocabulary else unknown_token for token in sentence]
        replaced_tokenized_sentences.append(replaced_sentence)
    return replaced_tokenized_sentences

def preprocess_data(train_data, test_data, count_threshold):
    vocabulary = get_words_with_nplus_frequency(train_data, count_threshold)
    train_data_replaced = replace_oov_words_by_unk(train_data, vocabulary)
    test_data_replaced = replace_oov_words_by_unk(test_data, vocabulary)
    return train_data_replaced, test_data_replaced, vocabulary

def count_n_grams(data, n, start_token='<s>', end_token='<e>'):
    n_grams = {}
    for sentence in data:
        sentence = [start_token] * n + sentence + [end_token]
        sentence = tuple(sentence)
        m = len(sentence) if n == 1 else len(sentence) - 1
        for i in range(m):
            n_gram = sentence[i:i + n]
            n_grams[n_gram] = n_grams.get(n_gram, 0) + 1
    return n_grams

def estimate_probability(word, previous_n_gram, n_gram_counts, n_plus1_gram_counts, vocabulary_size, k=1.0):
    previous_n_gram = tuple(previous_n_gram)
    previous_n_gram_count = n_gram_counts.get(previous_n_gram, 0)
    denominator = previous_n_gram_count + k * vocabulary_size
    n_plus1_gram = previous_n_gram + (word,)
    n_plus1_gram_count = n_plus1_gram_counts.get(n_plus1_gram, 0)
    numerator = n_plus1_gram_count + k
    probability = numerator / denominator
    return probability

def estimate_probabilities(previous_n_gram, n_gram_counts, n_plus1_gram_counts, vocabulary, k=1.0):
    previous_n_gram = tuple(previous_n_gram)
    vocabulary = vocabulary + ["<e>", "<unk>"]
    vocabulary_size = len(vocabulary)
    probabilities = {word: estimate_probability(word, previous_n_gram, n_gram_counts, n_plus1_gram_counts, vocabulary_size, k=k) for word in vocabulary}
    return probabilities

def suggest_a_word(previous_tokens, n_gram_counts, n_plus1_gram_counts, vocabulary, k=1.0, start_with=None):
    n = len(list(n_gram_counts.keys())[0])
    previous_n_gram = previous_tokens[-n:]
    probabilities = estimate_probabilities(previous_n_gram, n_gram_counts, n_plus1_gram_counts, vocabulary, k=k)
    suggestion = None
    max_prob = 0
    for word, prob in probabilities.items():
        if start_with and not word.startswith(start_with):
            continue
        if prob > max_prob:
            suggestion = word
            max_prob = prob
    return suggestion, max_prob

def get_suggestions(previous_tokens, n_gram_counts_list, vocabulary, k=1.0, start_with=None):
    suggestions = []
    for i in range(len(n_gram_counts_list) - 1):
        n_gram_counts = n_gram_counts_list[i]
        n_plus1_gram_counts = n_gram_counts_list[i + 1]
        suggestion = suggest_a_word(previous_tokens, n_gram_counts, n_plus1_gram_counts, vocabulary, k=k, start_with=start_with)
        suggestions.append(suggestion)
    return suggestions

# Example usage
if __name__ == "__main__":
    with open('[data path]', "r", encoding="utf8") as f:
        data = f.read()

    tokenized_data = get_tokenized_data(data)
    random.seed(87)
    random.shuffle(tokenized_data)

    train_size = int(len(tokenized_data) * 0.8)
    train_data = tokenized_data[:train_size]
    test_data = tokenized_data[train_size:]
    minimum_freq = 2
    train_data_processed, test_data_processed, vocabulary = preprocess_data(train_data, test_data, minimum_freq)

    n_gram_counts_list = [count_n_grams(train_data_processed, n) for n in range(1, 6)]

    # Example of how to get suggestions
    previous_tokens = ["hello", "how", "are"]
    suggestions = get_suggestions(previous_tokens, n_gram_counts_list, vocabulary, k=1.0, start_with="y")
    print(suggestions)

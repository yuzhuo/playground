

class Trie(object):
    def __init__(self):
        self.root = {}

    def add_word(self, word):
        node = self.root
        for c in word:
            if c not in node:
                node[c] = {}
            node = node[c]

        node['#'] = None # assume that word doesn't contain # character, we use it as word ending.

    def add_words(self, words):
        for w in words:
            self.add_word(w)

    def find(self, word):
        node = self.root
        for c in word:
            if c not in node:
                return False
            node = node[c]

        return '#' in node


def main():
    t = Trie()
    f = open("test.txt", "r")
    words = []
    for line in f:
        words.append(line.strip())
    t.add_words(words)
    f.close()

    for w in words:
        if not t.find(w):
            print "the trie doesn't contains %s" % w
            break

if __name__ == "__main__":
    main()



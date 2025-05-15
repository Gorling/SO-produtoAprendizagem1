class DFA:
    def __init__(self):
        self.q0 = 0  # Estado q0
        self.q1 = 1  # Estado q1
        self.q2 = 2  # Estado q2 (final)
        
        self.state = self.q0
      
        self.transitions = {
            self.q0: {'a': self.q1, 'b': self.q1},  # De q0 para q1 com 'a' ou 'b'
            self.q1: {'a': self.q2, 'b': self.q2},  # De q1 para q0 com 'a' ou q2 com 'b'
            self.q2: {'a': self.q1, 'b': self.q1},  # De q2 para q1 com 'a' ou q0 com 'b'
        }
        
        self.final_state = self.q2

    def process(self, input_string):
        for char in input_string:
            if char not in self.transitions[self.state]:
                return False  # Se a transição não existir, a string é rejeitada.
            self.state = self.transitions[self.state][char]
        
        return self.state == self.final_state

dfa = DFA()

test_strings = [
    "aabba",  # Rejeita
    "abab",    # Aceita
    "bbaa",    # Aceita
    "ab",      # Aceita
    "b",      # Rejeita
]

for test in test_strings:
    result = "Aceita" if dfa.process(test) else "Rejeita"
    print(f"'{test}': {result}")

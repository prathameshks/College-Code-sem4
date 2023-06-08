"""
Consider telephone book database of N clients. Make use of a hash table 
implementation to quickly look up client's telephone number. Make use of two collision 
handling techniques and compare them using number of comparisons required to find a 
set of telephone numbers
"""


class linear_probing:
    def __init__(self, m) -> None:
        self.m = m
        self.table = [[-1, ""] for _ in range(m)]

    def hash_fun(self, tel_no):
        return tel_no % self.m

    def insert(self, tel_no, name):
        hash = self.hash_fun(tel_no)

        if (self.table[hash][0] == -1):
            self.table[hash] = [tel_no, name]
        else:
            k = (hash+1) % self.m
            while (self.table[k][0] != -1 and hash != k):
                k = (k+1) % self.m
            if (hash == k):
                return False
            self.table[k] = [tel_no, name]
        return True

    def display(self):
        i = 0
        for rec in self.table:
            print(i, rec[0], rec[1], sep=" | ")
            i += 1

    def search(self, tel_no):
        hash = self.hash_fun(tel_no)

        if (self.table[hash][0] == -1):
            return False
        elif (self.table[hash][0] == tel_no):
            return self.table[hash][1]
        else:
            k = (hash+1) % self.m
            while (self.table[k][0] != tel_no and hash != k):
                k = (k+1) % self.m
            if (hash == k):
                return False
            else:
                return self.table[k][1]


class quadratic_probing:
    def __init__(self, m) -> None:
        self.m = m
        self.n = 0
        self.table = [[-1, ""] for _ in range(m)]

    def hash_fun(self, tel_no):
        return tel_no % self.m

    def insert(self, tel_no, name):
        if (self.n == self.m-1):
            return False
        hash = self.hash_fun(tel_no)

        if (self.table[hash][0] == -1):
            self.table[hash] = [tel_no, name]
            self.n += 1
        else:
            k = hash
            i = 1
            while (self.table[k][0] != -1):
                k = (k+i*i) % self.m
                i += 1
            self.table[k] = [tel_no, name]
            self.n += 1

        return True

    def display(self):
        i = 0
        for rec in self.table:
            print(i, rec[0], rec[1], sep=" | ")
            i += 1

    def search(self, tel_no):
        hash = self.hash_fun(tel_no)

        if (self.table[hash][0] == -1):
            return False
        elif (self.table[hash][0] == tel_no):
            return self.table[hash][1]
        else:
            k = (hash+1) % self.m
            i = 2
            while (self.table[k][0] != tel_no and self.table[k][0] != -1 and k != hash):
                k = (k+i*i) % self.m
                i += 1
            if (self.table[k][0] == -1 or hash == k):
                return False
            else:
                return self.table[k][1]


def main():
    a = quadratic_probing(10)
    print(a.insert(12, "A"))
    a.display()
    print(a.insert(22, "B"))
    print(a.insert(32, "C"))
    print(a.insert(45, "C"))
    print(a.insert(46, "C"))
    print(a.insert(72, "C"))
    print(a.insert(42, "C"))
    a.display()
    print(a.search(46))
    print(a.search(222))
    print(a.search(12))


main()

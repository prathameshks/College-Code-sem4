"""
To create ADT that implement the "set" concept. 
a. Add (new Element) -Place a value into the set , 
b. Remove (element) Remove the value 
c. Contains (element) Return true if element is in collection, 
d. Size () Return number of values in collection 
i. Iterator () Return an iterator used to loop over collection, 
e. Intersection of two sets , 
f. Union of two sets, 
g. Difference between two sets, 
h. Subset
"""


class set_adt:
    def __init__(self) -> None:
        self.items = []

    def add(self, elmt):
        if (elmt not in self.items):
            self.items.append(elmt)
            return True
        else:
            return False

    def remove(self, elmt):
        if (elmt in self.items):
            self.items.remove(elmt)
            return True
        else:
            return False

    def contains(self, elmt):
        return (elmt in self.items)

    def size(self):
        return len(self.items)

    def iterator(self):
        return iter(self.items)

    def intersection(self, set2):
        intersection = []
        for item in set2.iterator():
            if (self.contains(item)):
                intersection.append(item)
        return intersection

    def union(self, set2):
        union = self.items.copy()
        for item in set2.iterator():
            if (not set2.contains(item)):
                union.append(item)
        return union

    def difference(self, set2):
        diff = []
        for item in self.iterator():
            if (not set2.contains(item)):
                diff.append(item)
        return diff

    def subset(self, set2):
        for item in set2.iterator():
            if (not self.contains(item)):
                return False
        return True

def main():
    s = set_adt()
    print(s.add(1))
    print(s.add(1))
    print(s.add(2))
    print(s.add(3))
    s2 = set_adt()
    s2.add(1)
    s2.add(2)

    print(s.contains(1))
    print(s.contains(4))
    print(s2.remove(1))
    print(s.size())

    print(s.intersection(s2))
    print(s.union(s2))
    print(s.difference(s2))
    print(s.subset(s2))

if(__name__ == "__main__"):
    main()
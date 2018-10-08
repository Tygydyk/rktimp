class Node:

    def __init__(self, value = None, next = None):

        self.value = value

        self.next = next



class LinkedList:

    def __init__(self):

        self.first = None

        self.last = None

        self.length = 0



    def __str__(self):

        if self.first != None:

            current = self.first

            out = 'LinkedList [\n' +str(current.value) +'\n'

            while current.next != None:

                current = current.next

                out += str(current.value) + '\n'

            return out + ']'

        return 'LinkedList []'



    def clear(self):

        self.__init__()

        

    def add(self, x):

        self.length+=1

        if self.first == None:

            self.last = self.first = Node(x, None)

        else:

            self.last.next = self.last = Node(x, None)

            

    def push(self, x):

            self.length+=1

            if self.first == None:

                self.last = self.first = Node(x,None)

            else:

                self.first = Node(x,self.first)

    

    def InsertNth(self,i,x):

        if self.first == None:

            self.last = self.first = Node(x, None)

            return

        if i == 0:

          self.first = Node(x,self.first)

          return

        curr=self.first

        count = 0

        while curr != None:

            count+=1

            if count == i:

              curr.next = Node(x,curr.next)

              if curr.next.next == None:

                self.last = curr.next

              break

            curr = curr.next

            

    def len(self):

        length =0

        if self.first != None:

            current = self.first

            while current.next != None:

                current = current.next

                length +=1

        return length+1

        

    def Del(self,i):

        if (self.first == None):

          return

        curr = self.first

        old = self.first

        count = 0

        if i == 0:

          self.first = self.first.next

          return

        while curr != None:

            if count == i:

              if curr.next == None:

                self.last = curr

              old.next = curr.next 

              break

            old = curr  

            curr = curr.next

            count += 1

            

    def SortedInsert(self,x):

        if self.first == None:

          self.first = Node(x,self.last)

          return

        if self.first.value > x:

          self.first = Node(x,self.first)

          return

        curr = self.first

        old = self.first

        while curr != None:

            if curr.value > x:

              old.next = Node(x,curr)

              return

            old = curr

            curr = curr.next       

        self.last = old.next = Node(x,None)

        

    def RemoveDuplicates(self):

        if (self.first == None):

            return

        old=curr = self.first

        while curr != None:

            if curr.next != None:

                if old.value == curr.next.value:

                    curr.next = curr.next.next

            else:

                old=curr = old.next

            curr=curr.next

            

    def RemoveSortedDuplicates(self):

        if (self.first == None):

            return

        curr = self.first

        while curr != None:

            _del = 0 

            if curr.next != None:

                if curr.value == curr.next.value:

                    curr.next = curr.next.next

                    _del = 1

            if _del == 0:

                curr = curr.next

                

    def BubbleSort(self):

       a = Node(0,None)

       b = Node(0,None)

       c = Node(0,None)

       e = Node(0,None)

       tmp = Node(0,None)

       

       while(e != self.first.next) :

        c = a = self.first

        b = a.next



        while a != e:

          if a and b:

            if a.value > b.value:

              if a == self.first:

                tmp = b.next

                b.next = a

                a.next = tmp

                self.first = b

                c = b

              else:

                tmp = b.next

                b.next = a

                a.next = tmp

                c.next = b

                c = b

            else:

              c = a

              a = a.next

            b = a.next

            if b == e:

              e = a

          else:

              e = a

              

    def __getitem__(self, key):

        length =0

        current=None

        if self.first != None:

            current = self.first

            while key!=length or current.next != None:

                current = current.next

                length +=1

            if key==length:current=current.value

        return current



            

L = LinkedList()

L.add(1)

L.add(2)

L.add(3)

print(L)



import copy

L2 = copy.deepcopy(L)

print(L2)

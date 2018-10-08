template <typename _Key, typename _Tp,

	typename _Compare = std::less<_Key>,

	typename _Alloc = std::allocator<std::pair<const _Key, _Tp>>>

class multimap

    {

    public:

      typedef _Key                                          key_type;

      typedef _Tp                                           mapped_type;

      typedef std::pair<const _Key, _Tp>                    value_type;

      typedef _Compare                                      key_compare;

      typedef _Alloc                                        allocator_type;



    private:

// concept requirements

      typedef typename _Alloc::value_type                   _Alloc_value_type;

      __glibcxx_class_requires(_Tp, _SGIAssignableConcept)

      __glibcxx_class_requires4(_Compare, bool, _Key, _Key,

				_BinaryFunctionConcept)

      __glibcxx_class_requires2(value_type, _Alloc_value_type, _SameTypeConcept)	



    public:

class value_compare

      : public std::binary_function<value_type, value_type, bool>

      {

	friendclass multimap<_Key, _Tp, _Compare, _Alloc>;

protected:

	_Compare comp;



	value_compare(_Compare __c)

	: comp(__c) { }



      public:

	booloperator()(const value_type& __x, const value_type& __y) const

	{ return comp(__x.first, __y.first); }

      };



    private:

      typedef typename _Alloc::template rebind<value_type>::other 

        _Pair_alloc_type;



      typedef _Rb_tree<key_type, value_type, _Select1st<value_type>,

		       key_compare, _Pair_alloc_type> _Rep_type;

      _Rep_type _M_t;



    public:

      typedef typename _Pair_alloc_type::pointer         pointer;

      typedef typename _Pair_alloc_type::const_pointer   const_pointer;

      typedef typename _Pair_alloc_type::reference       reference;

      typedef typename _Pair_alloc_type::const_reference const_reference;

      typedef typename _Rep_type::iterator               iterator;

      typedef typename _Rep_type::const_iterator         const_iterator;

      typedef typename _Rep_type::size_type              size_type;

      typedef typename _Rep_type::difference_type        difference_type;

      typedef typename _Rep_type::reverse_iterator       reverse_iterator;

      typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;



      multimap()

      : _M_t(_Compare(), allocator_type()) { }



explicit

      multimap(const _Compare& __comp,

	const allocator_type& __a = allocator_type())

      : _M_t(__comp, __a) { }



      multimap(const multimap& __x)

      : _M_t(__x._M_t) { }



      template <typename _InputIterator>

        multimap(_InputIterator __first, _InputIterator __last)

	: _M_t(_Compare(), allocator_type())

        { _M_t._M_insert_equal(__first, __last); }



      template <typename _InputIterator>

        multimap(_InputIterator __first, _InputIterator __last,

		const _Compare& __comp,

		const allocator_type& __a = allocator_type())

        : _M_t(__comp, __a)

        { _M_t._M_insert_equal(__first, __last); }



      multimap&

operator=(const multimap& __x)

      {

	_M_t = __x._M_t;

	return *this;

      }



      allocator_type

      get_allocator() const

      { return _M_t.get_allocator(); }



      iterator

      begin()

      { return _M_t.begin(); }



      const_iterator

      begin() const

      { return _M_t.begin(); }



      iterator

      end()

      { return _M_t.end(); }



      const_iterator

      end() const

      { return _M_t.end(); }



      reverse_iterator

      rbegin()

      { return _M_t.rbegin(); }



      const_reverse_iterator

      rbegin() const

      { return _M_t.rbegin(); }



      reverse_iterator

      rend()

      { return _M_t.rend(); }



      const_reverse_iterator

      rend() const

      { return _M_t.rend(); }



bool

      empty() const

      { return _M_t.empty(); }



      size_type

      size() const

      { return _M_t.size(); }



      size_type

      max_size() const

      { return _M_t.max_size(); }



      iterator

      insert(const value_type& __x)

      { return _M_t._M_insert_equal(__x); }



      iterator

      insert(iterator __position, const value_type& __x)

      { return _M_t._M_insert_equal(__position, __x); }



      template <typename _InputIterator>

        void

        insert(_InputIterator __first, _InputIterator __last)

        { _M_t._M_insert_equal(__first, __last); }



      void

      erase(iterator __position)

      { _M_t.erase(__position); }



      size_type

      erase(const key_type& __x)

      { return _M_t.erase(__x); }



      void

      erase(iterator __first, iterator __last)

      { _M_t.erase(__first, __last); }



      void

      swap(multimap& __x)

      { _M_t.swap(__x._M_t); }



      void

      clear()

      { _M_t.clear(); }



      key_compare

      key_comp() const

      { return _M_t.key_comp(); }



      value_compare

      value_comp() const

      { return value_compare(_M_t.key_comp()); }



      iterator

      find(const key_type& __x)

      { return _M_t.find(__x); }



      const_iterator

      find(const key_type& __x) const

      { return _M_t.find(__x); }



      size_type

      count(const key_type& __x) const

      { return _M_t.count(__x); }



      iterator

      lower_bound(const key_type& __x)

      { return _M_t.lower_bound(__x); }



      const_iterator

      lower_bound(const key_type& __x) const

      { return _M_t.lower_bound(__x); }



      iterator

      upper_bound(const key_type& __x)

      { return _M_t.upper_bound(__x); }



      const_iterator

      upper_bound(const key_type& __x) const

      { return _M_t.upper_bound(__x); }



      std::pair<iterator, iterator>

      equal_range(const key_type& __x)

      { return _M_t.equal_range(__x); }



      std::pair<const_iterator, const_iterator>

      equal_range(const key_type& __x) const

      { return _M_t.equal_range(__x); }



      template <typename _K1, typename _T1, typename _C1, typename _A1>

friendbool

operator== (const multimap<_K1, _T1, _C1, _A1>&,

		const multimap<_K1, _T1, _C1, _A1>&);



      template <typename _K1, typename _T1, typename _C1, typename _A1>

friendbool

operator< (const multimap<_K1, _T1, _C1, _A1>&,

		const multimap<_K1, _T1, _C1, _A1>&);

  };



  template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>

inlinebool

operator==(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,

               const multimap<_Key, _Tp, _Compare, _Alloc>& __y)

    { return __x._M_t == __y._M_t; }



  template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>

inlinebool

operator<(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,

              const multimap<_Key, _Tp, _Compare, _Alloc>& __y)

    { return __x._M_t < __y._M_t; }



  template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>

inlinebool

operator!=(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,

               const multimap<_Key, _Tp, _Compare, _Alloc>& __y)

    { return !(__x == __y); }



  template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>

inlinebool

operator>(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,

              const multimap<_Key, _Tp, _Compare, _Alloc>& __y)

    { return __y < __x; }



  template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>

inlinebool

operator<=(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,

               const multimap<_Key, _Tp, _Compare, _Alloc>& __y)

    { return !(__y < __x); }



  template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>

inlinebool

operator>=(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,

               const multimap<_Key, _Tp, _Compare, _Alloc>& __y)

    { return !(__x < __y); }



  template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>

inline void

    swap(multimap<_Key, _Tp, _Compare, _Alloc>& __x,

         multimap<_Key, _Tp, _Compare, _Alloc>& __y)

    { __x.swap(__y); }



Java:



Класс SAX-анализатор:

/**

 * Методобработкиначалаэлемента

 */

  public void startElement(String uri, String Sname,

	String qname, Attributes attr)throws SAXException

    {

           // Обработка события на начало тэга 

	if(qname.equals("groupnode"))

          {

            try {

                baseObject = Class.forName(attr.getValue("baseobject"));

                parNameNode = attr.getValue("parnamenode");

                parent = Class.forName(attr.getValue("parent"));

                visible  =   new Boolean(attr.getValue("visible")).booleanValue();

                enabled =    new Boolean(attr.getValue("enabled")).booleanValue(); 

                parameter =   new Boolean(attr.getValue("parameter")).booleanValue(); 

                nameNode =  attr.getValue("namenode") ;

                // СоздаемэкземплярклассаGroupNode...

                //проверяем есть ли запрос с параметром

                if(parameter)

                {   

                          nameField = attr.getValue("nameField");

                          typeField = attr.getValue("typeField");

                          valueField = attr.getValue("valueField");

                          groupNode = new GroupNode(baseObject,nameNode,parNameNode, parent,

                          visible,enabled,parameter,nameField,typeField,valueField);



                }

                else

                    groupNode = new GroupNode(baseObject,nameNode, parNameNode,

                                       parent,visible,enabled,parameter);

                 listGroupNode.add(groupNode);

                } catch (ClassNotFoundException ex) 

                    {

                    ex.printStackTrace();

                    }



Созданиекорневыхэлементов:

listGroupNode = treeHandler.getListGroupNode();

       for (Object elem : listGroupNode) 

          {

            // проверяем загруженный список на наличие корневых нод

            if(javax.swing.tree.TreeNode.class.equals(((GroupNode) elem).getParentObj()))

            {

                root.add((GroupNode) elem);

             // проверяем есть ли запросы с параметром

             if(((GroupNode) elem).isParameter()){

                     // если есть проверяем какого типа параметр

                 if(((GroupNode) elem).getTypeField().equals("String"))

                     this.createNode((GroupNode) elem,queryDB.getParamColNto(

							((GroupNode) elem).getBaseObject(),

                                                        ((GroupNode) elem).getNameField(),

                                                        ((GroupNode) elem).getValueField(),

                                                            ((GroupNode) elem).getValueField()

                                                        )); 



                 if(((GroupNode) elem).getTypeField().equals("long"))    

                  this.createNode((GroupNode) elem,queryDB.getParamColNto(

							((GroupNode) elem).getBaseObject(),

                                                        ((GroupNode) elem).getNameField(),

                                 new Integer(((GroupNode) elem).getValueField()).intValue()

                                                           )); 



             }

             else 

                {

                     this.createNode((GroupNode) elem,queryDB.getColNto(

                                        ((GroupNode) elem).getBaseObject() )); 

                }



         }



Созданиеузлов:

public void createNode(DefaultMutableTreeNode groupNode,List   listNode){

         for (NodeTreeObj nto :listNode ) 

                        {

                            DefaultMutableTreeNode dtmT = new DefaultMutableTreeNode(nto);

                            groupNode.add(dtmT);

                           fillGroupNode((GroupNode) groupNode,dtmT);  

                        }

    }



Создание узла с объектом группировки:

void fillGroupNode(GroupNode groupNode,DefaultMutableTreeNode dmtn)

    {

        NodeTreeObj ntoL = (NodeTreeObj) dmtn.getUserObject();

            for (GroupNode  tmpGroupNode : this.getListGroupNode()) {

               if(tmpGroupNode.getParNameNode().equals(groupNode.toString()))

            {

                try{

                  // Определяем базовую бизнес сущность для узла группировки

                 if( tmpGroupNode.getParentObj() = = ntoL.getNameCls())

                      {

                     // Созданиеклассапошаблону

                       GroupNode realGroupNode =(GroupNode)tmpGroupNode.clone();

                       dmtn.add(realGroupNode);

                       fillNodeTree(realGroupNode, ntoL);

                      }

                   }catch(Exception ex){ex.printStackTrace();}

            }

        }

    }



Методзаполненияузла:

public void fillNodeTree(GroupNode fGroupNode, NodeTreeObj nto){



         try{

         Method meId = fGroupNode.getBaseObject().getMethod("getId");

          Method meName = fGroupNode.getBaseObject().getMethod("getName");

         // Находим метод вызова дочерних объектов определенного класса

Method nesMethod = this.getNesMethod(nto.getNameCls(), fGroupNode.getBaseObject());

         Object obj = queryDB.getObjTreeDB(nto);

         Set list = (Set) nesMethod.invoke(obj);

         if (list!=null){

         List listNto = new ArrayList();

        for ( Object elem : list) 

           {

              // вызываем эти методы и заносим полученные данные  в коллекцию

                  NodeTreeObj nto1 = new NodeTreeObj(

                             new Long(meId.invoke(elem).toString()).longValue(),

                             fGroupNode.getBaseObject(),

                            meName.invoke(elem).toString()

                            );    



                  listNto.add(nto1);

           } 

        this.createNode(fGroupNode,listNto);

         }

         }catch(Exception exp){ exp.printStackTrace();}



    }

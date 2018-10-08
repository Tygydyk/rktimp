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

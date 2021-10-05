Для подклюения библиотеки opencascade сделано:

0) Добавлена в ОС переменная среды OCCT со значением C:\OpenCASCADE-7.4.0-vc14-64\opencascade-7.4.0\
1) скачан и установлен бинарник opencascade версии OpenCASCADE-7.4.0-vc14-64

2) добавлен с++ проект OCCTProxy (в свойствах решения выставленна зависимость RustedNail от OCCProxy), оба проекта собираются в ..\win64\bind. Этот проект нужен для получения OCCTProxy.dll являющейся .net сборкой и выполняющей роль "интерфейса" к библиотекам opencascade написанным на c++
 2.1) в ..\win64\bind скопированны DLL third party из C:\OpenCASCADE-7.4.0-vc14-64 типа freeimage и freetype
 2.2.)в ..\win64\bind скопированны DLL из C:\OpenCASCADE-7.4.0-vc14-64\opencascade-7.4.0\win64\vc14\bin (не все они использованы, применение каждой из них зависит от исходника) 
3) в проект добавленна ссылка на сборку OCCTProxy
4) в конфигурации проекта задана целевая платформа x64 (для связки с библиотекос OCCT)
5) Код
 5.1) в главной форме поле myModelFormat
 5.2) обработчик создания дочернего окна
 5.3) в дочерней форме перечисления : CurrentAction3d, CurrentPressedKey,ModelFormat. Поля :  myOCCTProxy; myCurrentMode; myCurrentPressedKey. Свойство View. Конструктор и методы InitV3D, InitView. Обработчики событий SizeChanged, Paint, MouseMove,....





УПРАВЛЕНИЕ:
Ctrl + LMB = zoom
Ctrl + MMB = paning
Ctrl + RMB = rotation

BRepPrimAPI_MakeCylinder
BRepFeat_MakeCylindricalHole
BRepBuilderAPI_Transform
BRepAlgoAPI_Cut
BRepPrimAPI_MakeTorus
BRepAlgoAPI_Fuse
BRepBuilderAPI_MakeWire
BRepBuilderAPI_MakeEdge
BRepBuilderAPI_MakeFace
BRepPrimAPI_MakeRevol
BRepBuilderAPI_Transform
BRepAlgoAPI_Cut
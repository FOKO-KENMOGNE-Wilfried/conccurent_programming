int DisplayInterfacesClass::DisplayApp(QApplication a, std::list<Human*> humanList)
{
    // QApplication a(argc, argv);
    View w(nullptr, humanList);
    // Kitchen k;
    w.show();
    // k.show();
    return a.exec();
}
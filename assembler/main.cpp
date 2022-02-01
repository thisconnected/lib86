#include <QCommandLineParser>
#include <QString>
#include "assembler.hpp"



int main(int argc, char **argv)
{
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("Lib86");
  QCommandLineParser parser;
  parser.setApplicationDescription("8086 Emulator");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("source", QCoreApplication::translate("main", "x86 emu8086-style assembly"));
  parser.addPositionalArgument("destination", QCoreApplication::translate("main", "Where to write binary"));
  parser.process(app);

  const QStringList args = parser.positionalArguments();

  if(args.count() < 2)
    parser.showHelp(-1);

  assembler ass = new assembler();



}

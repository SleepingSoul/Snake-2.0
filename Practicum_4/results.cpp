#include "results.h"
#include "mainmenu.h"
#include <cassert>
#include <QtAlgorithms>

#define Enter_key 16777220
#define Backspace_key 16777219
#define Shift_key 16777248
#define Space_key 32

Results::Results( GameWidget *gw ) : gw( gw ), nicknameEntered( true ), offset( 0 )
{
    button_back.load( ":/images/Images/button_back.png" );
    name_field_image.load( ":/images/Images/name_field.png" );
    inResultsFile.open( "results.dat", ios::in );
    if ( !inResultsFile )
        assert( "can not open results file for reading" );

    gw->update();
}

Results::Results( GameWidget *gw, unsigned points ) : gw( gw ), points( points ), nicknameEntered( false )
{
    button_back.load( ":/images/Images/button_back.png" );
    name_field_image.load( ":/images/Images/name_field.png" );
    outResultsFile.open( "results.dat", ios::app );
    inResultsFile.open( "results.dat", ios::in );
    if ( !outResultsFile )
        assert( "no results file" );
    if ( !inResultsFile )
        assert( "can not open results file for reading" );

    gw->update();
}

Results::~Results()
{
    outResultsFile.close();
    inResultsFile.close();
}

void Results::paint()
{
    gw->painter->begin( gw );
    gw->painter->drawPixmap( gw->rect(), QPixmap( ":/images/Images/scrreen_results.png" ) );
    gw->painter->drawImage( 15, 15, button_back );
    if ( !nicknameEntered ) {
        gw->painter->drawImage( 360, 300, name_field_image );
        gw->painter->setPen( QPen( Qt::white ) );
        if ( !nickname.isEmpty() ) {
            gw->painter->setFont( QFont( "Times", 18, QFont::Bold ) );
            for ( int i = 0; i < nickname.size(); i++ )
                gw->painter->drawText( gw->width() / 2 - 10 * offset + 20 * i, 370, QString( nickname[ i ] ) );
        }
    }
    else {
        gw->painter->setPen( QPen( Qt::white ) );
        gw->painter->setFont( QFont( "Times", 18, QFont::Bold ) );
        unsigned points;
        char name[ 30 ];
        int i = 0;
        QList<QString> resList;
        QMap<unsigned, QString> namesAndPoints;
        while ( inResultsFile >> points >> name  ) {
            QString str;
            resList.append( QString( str.number( points ) + "        " + name ) );
            namesAndPoints.insert( points, QString( name ) );
        }
        QString str;
        auto num = namesAndPoints.keyEnd();
        auto it = namesAndPoints.cend();
        for ( ; it != namesAndPoints.cbegin(); ) {
            --it;
            --num;
            gw->painter->drawText( 360, 50 + 30 * i, *it );
            gw->painter->drawText( 700, 50 + 30 * i++, str.number( *num ) );
        }
    }
    gw->painter->end();
}

void Results::mouseReleased( QMouseEvent *event )
{
    int x = event->pos().x();
    int y = event->pos().y();
    if ( x >= 15 && x <= 213 && y >= 15 && y <= 64 )
        gw->setState( new MainMenu( gw ) );
}

void Results::keyPressed( QKeyEvent *event )
{
    if ( !nicknameEntered ) {
        qDebug() << event->key();
        nickname.push_back( /*event->text().toStdString().c_str()[ 0 ]*/ event->key() );
        if ( event->key() == Enter_key ) {
            nickname.remove( Enter_key );
            outResultsFile << points << "   " << nickname.toStdString().data() << endl;
            nicknameEntered = true;
        }
        if ( event->key() == Backspace_key ) {
            nickname.remove( Backspace_key );
            if ( !nickname.isEmpty() )
                nickname.remove( nickname.size() - 1, 1 );
        }
        if ( event->key() == Shift_key ) {
            nickname.remove( Shift_key );
        }
        if ( event->key() == Space_key ) {
            nickname.remove( Space_key );
            nickname.append( "_" );
        }
        offset = nickname.size();
        gw->update();
     }
}

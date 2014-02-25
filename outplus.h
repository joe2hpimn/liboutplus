/*
    liboutplus - C structured output library

    outplus.h - definitions and prototypes for outplus

    Copyright (C) 2012 - 2014 Jan Seidl

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OUTPUT_H
#define OUTPUT_H

/* Macros */

#ifndef OUTPLUS_KEY_MAX_LEN
#define OUTPLUS_KEY_MAX_LEN 255

#ifndef OUTPLUS_VALUE_MAX_LEN
#define OUTPLUS_VALUE_MAX_LEN 1000

#ifndef OUTPLUS_TITLE_MAX_LEN
#define OUTPLUS_TITLE_MAX_LEN 1000

#ifndef OUTPLUS_HTML_TITLE
#define OUTPLUS_HTML_TITLE "Outplus Output"

#ifndef OUTPLUS_HTML_HEAD 
#define OUTPLUS_HTML_HEAD "<!DOCTYPE HTML>\n<html>\n\t<head>\n\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\t\t<title>" OUTPLUS_HTML_TITLE " Output</title>\n\t\t<style type=\"text/css\">\n\t\t\tbody { font-family: Sans, Arial; }\n\t\t\th1 { padding-top: 11px; padding-bottom: 11px; padding-left: 70px; }\n\t\t\th2,h3,h4,h5 { clear: both; float: none; margin-bottom: 0px; }\n\t\t\tdl { margin-bottom: 20px; float: left; }\n\t\t\t.even { background-color: #EEE; }\n\t\t\tdt { padding: 2px 5px; float: left; margin-right: 0px; clear: left; width: 240px; font-weight: bold; margin-bottom: 5px; font-weight: bold; }\n\t\t\tdd { width: 360px; margin-left: 0px; padding: 2px 5px; float: left; }\n\t\t</style>\n\t</head>\n\t<body>\n"

#ifndef OUTPLUS_HTML_FOOTER
#define OUTPLUS_HTML_FOOTER "\t</body>\n</html>"

#ifndef OUTPLUS_XML_HEAD
#define OUTPLUS_XML_HEAD "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<output>\n"

#ifndef OUTPLUS_XML_FOOTER
#define OUTPLUS_XML_FOOTER "</output>"

/* structs, enums, typedefs etc... */

typedef enum {
    OUTPLUS_FORMAT_TEXT = 1,
    OUTPLUS_FORMAT_HTML = 2,
    OUTPLUS_FORMAT_XML = 3,
    OUTPLUS_FORMAT_CSV = 4,
    OUTPLUS_FORMAT_JSON = 5
} OUTPLUS_FORMAT_E;

OUTPLUS_FORMAT_E outplus_format;

typedef struct _OUTPLUS_SECTOR
{

    char title[OUTPLUS_TITLE_MAX_LEN];

    struct _OUTPLUS_LINE *first_line;

    struct _OUTPLUS_SECTOR *parent;
    struct _OUTPLUS_SECTOR *child;

    struct _OUTPLUS_SECTOR *next;
    struct _OUTPLUS_SECTOR *prev;

} OUTPLUS_SECTOR;//end :: struct :: _OUTPLUS_SECTOR

typedef struct _OUTPLUS_LINE
{
    char key[OUTPLUS_KEY_MAX_LEN];
    char value[OUTPLUS_VALUE_MAX_LEN];

    struct _OUTPLUS_LINE *next;
    struct _OUTPLUS_LINE *prev;
} OUTPLUS_LINE;//end :: struct :: _OUTPLUS_LINE

/* Prototypes */
// Core Functions
OUTPLUS_SECTOR * outplus_get_last_sector(OUTPLUS_SECTOR *sector);
OUTPLUS_SECTOR * outplus_add_sector(char *name, OUTPLUS_SECTOR ** current_OUTPLUS_SECTOR);
OUTPLUS_SECTOR * outplus_add_child_sector(char *name, OUTPLUS_SECTOR ** current_OUTPLUS_SECTOR);
OUTPLUS_LINE * outplus_get_last_sector_line(OUTPLUS_SECTOR *sector);
OUTPLUS_LINE outplus_add_line(char *key, char *value, OUTPLUS_SECTOR *sector);

// Output Parsers
void outplus_dump_text(OUTPLUS_SECTOR *sector);
void outplus_dump_html(OUTPLUS_SECTOR *sector);
void outplus_dump_xml(OUTPLUS_SECTOR *sector);
void outplus_dump_csv(OUTPLUS_SECTOR *sector);
void outplus_dump_json(OUTPLUS_SECTOR *sector);

void outplus_dump(OUTPLUS_SECTOR *sector);

void outplus_dump_sector_xml(OUTPLUS_SECTOR *sector, unsigned int depth);
void outplus_dump_sector_text(OUTPLUS_SECTOR *sector, unsigned int depth);
void outplus_dump_sector_csv(OUTPLUS_SECTOR *sector, unsigned int depth);
void outplus_dump_sector_html(OUTPLUS_SECTOR *sector, unsigned int depth);
void outplus_dump_sector_json(OUTPLUS_SECTOR *sector, unsigned int depth);

// Util Functions
void outplus_free_output(OUTPLUS_SECTOR *sector);
void outplus_parse_format(const char *optarg);
char *outplus_slug(char *string);
char *outplus_create_tabs(unsigned int count);

// Parser functions
void outplus_html_print_header();
void outplus_html_print_footer();
void outplus_xml_print_header();
void outplus_xml_print_footer();
#endif

#ifndef TXML_APPLICATION_FB2_FWD_H
#define TXML_APPLICATION_FB2_FWD_H

#include <txml/txml_fwd.h>

#include <txml/applications/fb2/auxiliary/fb2_aux_fwd.h>
#include <txml/applications/fb2/body/fb2_body_fwd.h>
#include <txml/applications/fb2/common/fb2_common_fwd.h>

#include <txml/applications/fb2/include/fwd/BookTitle.h>
#include <txml/applications/fb2/include/fwd/Genre.h>
#include <txml/applications/fb2/include/fwd/Language.h>
#include <txml/applications/fb2/include/fwd/Description.h>
#include <txml/applications/fb2/include/fwd/DocumentInfo.h>
#include <txml/applications/fb2/include/fwd/Empty.h>
#include <txml/applications/fb2/include/fwd/FB2TextElement.h>
#include <txml/applications/fb2/include/fwd/FictionBook.h>
#include <txml/applications/fb2/include/fwd/PublishInfo.h>
#include <txml/applications/fb2/include/fwd/Publisher.h>
#include <txml/applications/fb2/include/fwd/ISBN.h>
#include <txml/applications/fb2/include/fwd/TitleInfo.h>
#include <txml/applications/fb2/include/fwd/Author.h>
#include <txml/applications/fb2/include/fwd/FirstName.h>
#include <txml/applications/fb2/include/fwd/MiddleName.h>
#include <txml/applications/fb2/include/fwd/LastName.h>
#include <txml/applications/fb2/include/fwd/NickName.h>

#define FB2_CLASS_LIST      fb2::FictionBook, fb2::Description, fb2::Body, fb2::Binary,             \
                            fb2::TitleInfo, fb2::DocumentInfo, fb2::PublishInfo,                    \
                            fb2::BookTitle, fb2::Genre, fb2::Language,                              \
                            fb2::Author, fb2::Publisher, fb2::ISBN,                                 \
                            fb2::FirstName, fb2::MiddleName, fb2::LastName, fb2::NickName,          \
                            fb2::Section,                                                           \
                            fb2::Paragraph,                                                         \
                            fb2::FB2TextElement, fb2::Empty

#endif // TXML_APPLICATION_FB2_FWD_H

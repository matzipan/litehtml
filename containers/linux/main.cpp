
#include <litehtml.h>
#include "container_linux.h"
#include <gtkmm/application.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>


class container_gtk : public container_linux {
  virtual Glib::RefPtr<Gdk::Pixbuf>	get_image(const litehtml::tchar_t* url, bool redraw_on_ready)  {
    return (Glib::RefPtr<Gdk::Pixbuf>) nullptr;
  }

  virtual void    set_caption(const litehtml::tchar_t* caption) {

  }

  virtual void    set_base_url(const litehtml::tchar_t* base_url) {

  }

  virtual void    on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el) {

  }

  virtual void    set_cursor(const litehtml::tchar_t* cursor) {

  }

  virtual void    import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) {

  }

  virtual void    get_client_rect(litehtml::position& client) const {

  }
};

class MyArea : public Gtk::DrawingArea
{

  std::shared_ptr<litehtml::document> document;
public:
  MyArea(std::shared_ptr<litehtml::document> document) : Gtk::DrawingArea(), document(document) {
    add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
  }
  ~MyArea() {}

protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    const auto clip = litehtml::position(0, 0, width, height);

    document->draw((litehtml::uint_ptr)cr->cobj(), 0, 0, &clip);
  }

  bool on_button_press_event(GdkEventButton *event)
{
    if(document)
    {
        litehtml::position::vector redraw_boxes;
        if(document->on_lbutton_down((int) event->x, (int) event->y, (int) event->x, (int) event->y, redraw_boxes))
        {
            for(auto& pos : redraw_boxes)
            {
                queue_draw_area(pos.x, pos.y, pos.width, pos.height);
            }
        }
    }
    return true;
}

bool on_motion_notify_event(GdkEventMotion *event)
{
    if(document)
    {
        litehtml::position::vector redraw_boxes;
        if(document->on_mouse_over((int) event->x, (int) event->y, (int) event->x, (int) event->y, redraw_boxes))
        {
            for(auto& pos : redraw_boxes)
            {
                queue_draw_area(pos.x, pos.y, pos.width, pos.height);
            }
        }
    }
	return true;
}

bool on_button_release_event(GdkEventButton *event)
{
    if(document)
    {
        litehtml::position::vector redraw_boxes;
		// m_clicked_url.clear();
        if(document->on_lbutton_up((int) event->x, (int) event->y, (int) event->x, (int) event->y, redraw_boxes))
        {
            for(auto& pos : redraw_boxes)
            {
                queue_draw_area(pos.x, pos.y, pos.width, pos.height);
            }
        }
		// if(!m_clicked_url.empty())
		// {
		// 	// m_browser->open_url(m_clicked_url);
		// }
    }
    return true;
}
};

int main(int argc, char** argv) {
  container_gtk container_linux;
  litehtml::context litehtml_context;

  litehtml_context.load_master_stylesheet(R"MASTER(
    html {
        display: block;
        width: 100%;
        height: 100%;
    	position: relative;
    }

    head {
        display: none;
    }

    meta {
        display: none;
    }

    title {
        display: none;
    }

    link {
        display: none;
    }

    style {
        display: none;
    }

    script {
        display: none;
    }

    body {
    	display:block;
    	margin:8px;
        height:100%;
        width:100%;
    }

    p {
    	display:block;
    	margin-top:1em;
    	margin-bottom:1em;
    }

    b, strong {
    	display:inline;
    	font-weight:bold;
    }

    i, em {
    	display:inline;
    	font-style:italic;
    }

    center
    {
    	text-align:center;
    	display:block;
    }

    a:link
    {
    	text-decoration: underline;
    	color: #00f;
    	cursor: pointer;
    }

    h1, h2, h3, h4, h5, h6, div {
    	display:block;
    }

    h1 {
    	font-weight:bold;
    	margin-top:0.67em;
    	margin-bottom:0.67em;
    	font-size: 2em;
    }

    h2 {
    	font-weight:bold;
    	margin-top:0.83em;
    	margin-bottom:0.83em;
    	font-size: 1.5em;
    }

    h3 {
    	font-weight:bold;
    	margin-top:1em;
    	margin-bottom:1em;
    	font-size:1.17em;
    }

    h4 {
    	font-weight:bold;
    	margin-top:1.33em;
    	margin-bottom:1.33em
    }

    h5 {
    	font-weight:bold;
    	margin-top:1.67em;
    	margin-bottom:1.67em;
    	font-size:.83em;
    }

    h6 {
    	font-weight:bold;
    	margin-top:2.33em;
    	margin-bottom:2.33em;
    	font-size:.67em;
    }

    br {
    	display:inline-block;
    }

    br[clear="all"]
    {
    	clear:both;
    }

    br[clear="left"]
    {
    	clear:left;
    }

    br[clear="right"]
    {
    	clear:right;
    }

    span {
    	display:inline
    }

    img {
    	display: inline-block;
    }

    img[align="right"]
    {
    	float: right;
    }

    img[align="left"]
    {
    	float: left;
    }

    hr {
        display: block;
        margin-top: 0.5em;
        margin-bottom: 0.5em;
        margin-left: auto;
        margin-right: auto;
        border-style: inset;
        border-width: 1px
    }


    /***************** TABLES ********************/

    table {
        display: table;
        border-collapse: separate;
        border-spacing: 2px;
        border-top-color:gray;
        border-left-color:gray;
        border-bottom-color:black;
        border-right-color:black;
    }

    tbody, tfoot, thead {
    	display:table-row-group;
    	vertical-align:middle;
    }

    tr {
        display: table-row;
        vertical-align: inherit;
        border-color: inherit;
    }

    td, th {
        display: table-cell;
        vertical-align: inherit;
        border-width:1px;
        padding:1px;
    }

    th {
    	font-weight: bold;
    }

    table[border] {
        border-style:solid;
    }

    table[border|=0] {
        border-style:none;
    }

    table[border] td, table[border] th {
        border-style:solid;
        border-top-color:black;
        border-left-color:black;
        border-bottom-color:gray;
        border-right-color:gray;
    }

    table[border|=0] td, table[border|=0] th {
        border-style:none;
    }

    caption {
    	display: table-caption;
    }

    td[nowrap], th[nowrap] {
    	white-space:nowrap;
    }

    tt, code, kbd, samp {
        font-family: monospace
    }

    pre, xmp, plaintext, listing {
        display: block;
        font-family: monospace;
        white-space: pre;
        margin: 1em 0
    }

    /***************** LISTS ********************/

    ul, menu, dir {
        display: block;
        list-style-type: disc;
        margin-top: 1em;
        margin-bottom: 1em;
        margin-left: 0;
        margin-right: 0;
        padding-left: 40px
    }

    ol {
        display: block;
        list-style-type: decimal;
        margin-top: 1em;
        margin-bottom: 1em;
        margin-left: 0;
        margin-right: 0;
        padding-left: 40px
    }

    li {
        display: list-item;
    }

    ul ul, ol ul {
        list-style-type: circle;
    }

    ol ol ul, ol ul ul, ul ol ul, ul ul ul {
        list-style-type: square;
    }

    dd {
        display: block;
        margin-left: 40px;
    }

    dl {
        display: block;
        margin-top: 1em;
        margin-bottom: 1em;
        margin-left: 0;
        margin-right: 0;
    }

    dt {
        display: block;
    }

    ol ul, ul ol, ul ul, ol ol {
        margin-top: 0;
        margin-bottom: 0
    }

    blockquote {
    	display: block;
    	margin-top: 1em;
    	margin-bottom: 1em;
    	margin-left: 40px;
    	margin-left: 40px;
    }

    /*********** FORM ELEMENTS ************/

    form {
    	display: block;
    	margin-top: 0em;
    }

    option {
    	display: none;
    }

    input, textarea, keygen, select, button, isindex {
    	margin: 0em;
    	color: initial;
    	line-height: normal;
    	text-transform: none;
    	text-indent: 0;
    	text-shadow: none;
    	display: inline-block;
    }
    input[type="hidden"] {
    	display: none;
    }


    article, aside, footer, header, hgroup, nav, section
    {
    	display: block;
    }



    a:hover {
      color: #f00;
    }



    html {
      width:auto;
      height:auto;
    }
  )MASTER");
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  Gtk::Window win;
  win.set_title("DrawingArea");

  auto document = litehtml::document::createFromString("<!DOCTYPE html><html><body><a href=\"\">Click Me!</a><p style=\"border: 1px solid #000\">BLA</p><p>asdf</p><br><ul><li>list here</li></ul>\n<div>MORE STUFF HERE<br>MORE STUFF HERE</div></body></html>", static_cast<litehtml::document_container*>(&container_linux), &litehtml_context);

  document->render(300);


  MyArea area(document);
  area.set_size_request(document->width(), document->height());

  win.add(area);
  area.show();


  return app->run(win);

  return 0;
}

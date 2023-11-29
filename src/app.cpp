#include "app.hpp"

#include <cstdio>
#include <iostream>

#include "ImFrame.h"
#include "imgui.h"
#include "implot.h"
#include "lv_conf.h"
#include "lvgl.h"
#include "lvgl_demo/lv_demo_widgets.h"


struct Mouse
{
    bool is_pressed = false;
    int16_t x       = 0;
    int16_t y       = 0;
};

static Mouse s_mouse;

static constexpr unsigned int DISP_HOR_RES = 256;
static constexpr unsigned int DISP_VER_RES = 256;
static constexpr int DISP_BUF_SIZE         = DISP_HOR_RES * DISP_VER_RES / 10;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[DISP_BUF_SIZE]; /*Declare a buffer for 1/10 screen size*/

ImFrame::ImageInfo display_buffer;

extern "C"
{
    static void btn_event_cb(lv_event_t* e)
    {
        lv_event_code_t code = lv_event_get_code(e);
        lv_obj_t* btn        = lv_event_get_target(e);
        if (code == LV_EVENT_CLICKED)
        {
            static uint8_t cnt = 0;
            cnt++;

            /*Get the first child of the button which is the label and change its text*/
            lv_obj_t* label = lv_obj_get_child(btn, 0);
            lv_label_set_text_fmt(label, "Button: %d", cnt);
        }
    }

    /**
     * Create a button with a label and react on click event.
     */
    void lv_example_get_started_1(void)
    {
        lv_obj_t* btn = lv_btn_create(lv_scr_act());                /*Add a button the current screen*/
        lv_obj_set_pos(btn, 10, 10);                                /*Set its position*/
        lv_obj_set_size(btn, 120, 50);                              /*Set its size*/
        lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL); /*Assign a callback to the button*/

        lv_obj_t* label = lv_label_create(btn); /*Add a label to the button*/
        lv_label_set_text(label, "Button");     /*Set the labels text*/
        lv_obj_center(label);
    }

    // Function to set RGBA values at a specific (x, y) position
    void set_pixel(std::vector<uint8_t>& image, int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    {
        // Calculate the index in the vector for the specified (x, y) position
        int index = 4 * (y * DISP_HOR_RES + x);

        // Set the RGBA values at the calculated index
        image[index]     = red;
        image[index + 1] = green;
        image[index + 2] = blue;
        image[index + 3] = alpha;
    }


    void my_disp_flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
    {
        /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one
         *`put_px` is just an example, it needs to implemented by you.*/
        int32_t x, y;
        for (y = area->y1; y <= area->y2; y++)
        {
            for (x = area->x1; x <= area->x2; x++)
            {
                set_pixel(display_buffer.data, x, y, color_p->ch.red, color_p->ch.green, color_p->ch.blue,
                          color_p->ch.alpha);
                color_p++;
            }
        }

        /* IMPORTANT!!!
         * Inform the graphics library that you are ready with the flushing*/
        lv_disp_flush_ready(disp_drv);
    }

    void my_touchpad_read(lv_indev_drv_t* indev, lv_indev_data_t* data)
    {
        (void)indev;
        (void)data;
        /*`touchpad_is_pressed` and `touchpad_get_xy` needs to be implemented by you*/
        if (s_mouse.is_pressed)
        {
            data->state   = LV_INDEV_STATE_PRESSED;
            data->point.x = s_mouse.x;
            data->point.y = s_mouse.y;
        }
        else
        {
            data->state = LV_INDEV_STATE_RELEASED;
        }
    }
};

namespace app
{

    Canerator::Canerator()
    {
        display_buffer.data.resize(DISP_VER_RES * DISP_HOR_RES * 4);
        display_buffer.height   = DISP_VER_RES;
        display_buffer.width    = DISP_HOR_RES;
        display_buffer.channels = 4;

        lv_init();

        /*Initialize the display buffer.*/
        lv_disp_draw_buf_init(&draw_buf, buf1, NULL, DISP_BUF_SIZE);

        static lv_disp_drv_t disp_drv;     /*Descriptor of a display driver*/
        lv_disp_drv_init(&disp_drv);       /*Basic initialization*/
        disp_drv.flush_cb = my_disp_flush; /*Set your driver function*/
        disp_drv.draw_buf = &draw_buf;     /*Assign the buffer to the display*/
        disp_drv.hor_res  = DISP_HOR_RES;  /*Set the horizontal resolution of the display*/
        disp_drv.ver_res  = DISP_VER_RES;  /*Set the vertical resolution of the display*/
        lv_disp_drv_register(&disp_drv);   /*Finally register the driver*/

        static lv_indev_drv_t indev_drv;           /*Descriptor of a input device driver*/
        lv_indev_drv_init(&indev_drv);             /*Basic initialization*/
        indev_drv.type    = LV_INDEV_TYPE_POINTER; /*Touch pad is a pointer-like device*/
        indev_drv.read_cb = my_touchpad_read;      /*Set your driver function*/
        lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/


        // lv_example_get_started_1();
        std::cout << "Hi from C++, this is a demo how LuaCpp can be used"
                  << "\n";

        lv_demo_widgets();

        // The simples way is to use CompileStringAndRun method
        try
        {
            // lua.CompileStringAndRun("print('The fastest way to start using lua in a project')");
            lua_.CompileFile("main", "scripts/main.lua");
        }
        catch (std::runtime_error& e)
        {
            std::cout << e.what() << '\n';
        }
    }

    Canerator::~Canerator()
    {
    }

    void Canerator::Update()
    {
        lv_tick_inc(5);
        lv_timer_handler();

        // ImGui::ShowDemoWindow();
        // ImPlot::ShowDemoWindow();

        ImGui::Begin("Debug");
        ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Begin("Canerator");

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (ImGui::Button("Execute Lua Script"))
        {
            lua_.Run("main");
        }

        if (ImGui::Button("File Explorer"))
        {
            ImFrame::OpenFileDialog({{"Image files", "png,jpg"}}, nullptr);
        }


        ImGui::End();

        ImGui::Begin("LVGL", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
        auto image_ret = ImFrame::LoadTexture(display_buffer);
        auto image     = image_ret.value();

        ImGui::Image((void*)image.textureID, ImVec2((float)image.width, (float)image.height));

        ImGui::End();
    }

    void Canerator::UpdateMouseButton(int button, int action, int mods)
    {
        s_mouse.is_pressed = action;
        printf("%d, %d, %d\n", button, action, mods);
    }

    void Canerator::UpdateMousePosition(double x, double y)
    {
        s_mouse.x = std::round(x) - 16;
        s_mouse.y = std::round(y) - 16;
        printf("%f, %f\n", x, y);
    }

}  // namespace app

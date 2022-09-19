#pragma once
#include "glew.h"
#include "glfw3.h"
#include "Display.h"




int main()
{ 
   
    
    Display* dis = new Display();
    std::vector<float> buffer_data =
    { -0.5f, -0.5f, 0.0f, 0.0f,
       0.5f, -0.5f, 1.0f, 0.0f,
       0.5f, 0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f , 0.0f, 1.0f
    }; 

    VertexArray va;
    VertexBuffer buffer = VertexBuffer(buffer_data); 
    std::vector<unsigned int> count = {2, 2};
    std::vector<unsigned int> type = { GL_FLOAT, GL_FLOAT };
    BufferLayout layout = BufferLayout(count, type);  
    buffer.BindLayout(layout); 
    va.AddBuffer(buffer);  


    unsigned int indices[6] =  
    { 0, 1, 2, 
      2, 3, 0  
    };
    IndexBuffer index_buffer = IndexBuffer(indices, 6);


    Texture text = Texture("res/images/test.png");
    text.Bind(); 


    std::string filepath = "res/shader/Texture.shader"; 

    Shader shader = Shader(filepath); 

    //int u_Color = shader.Get_Uniform("u_Color"); 
    //shader.Set_Uniform4f(u_Color, 0.2f, 0.5f, 0.8f); 

    shader.SetUniform1i("u_Texture", 0);

    Template t = Template(shader, index_buffer, buffer); 

    int counter = 0;

    while (!glfwWindowShouldClose(Display::window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        //shader.Set_Uniform4f(t.shader->uniforms[u_Color], red, blue, green); 
        Display::Draw_Index_Buffer_Texture(t, text);  

        if (counter < 50)
        {
            buffer.Transform(0.01f, 0.0f);
            counter += 1;
        }
        if (counter >= 50)
        {
            buffer.Transform(-1.0f, 0.0f);
            counter = -50;
        }
        va.AddBuffer(buffer); 

        /* Swap front and back buffers */
        glfwSwapBuffers(Display::window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    glfwTerminate();

    std::cout << "\a" << std::endl; 
    return 0;
}

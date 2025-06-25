#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "SpriteAnimado.h"
#include <GLFW/glfw3.h>

class CharacterController {
public:
    CharacterController(GLFWwindow* win, GLuint shaderID);
    void atualizar(float deltaTime);
    void desenhar();

private:
    GLFWwindow* janela;
    SpriteAnimado* spriteAtual;
    SpriteAnimado spriteFrente, spriteCosta, spriteEsquerda, spriteDireita;
    SpriteAnimado spriteFrenteIdle, spriteCostaIdle, spriteEsquerdaIdle, spriteDireitaIdle;
    glm::vec2 posicao;
    float velocidade;
};

#endif

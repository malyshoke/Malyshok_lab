#pragma once

struct Pipe
{
    int id;
    double length;
    double diameter;
};

void print_pipe(Pipe& pipe);

void input_pipe(Pipe& pipe);

# NVF Controls

This is the main repository for the [Nanyang Venture Formula](.) Racing Team's data acquisition subsystem. Contents for work and their documentation includes:

## Overall System Architecture

We strife to adopt the "1 Job" modality, where every node in every system should only do 1 Job, and be best at it.

Enough? We think not! Each component will have a failsafe. The system is deisgned in a way that there **should** not have any single point of failures (at least for critical components). For example, there are 2 Vehicle Control Units (VCUs) that both serve the same purpose and run **concurrently**.

To segregate systems, seperate CanBus networks will be used. Namely:

1. VCU
2. Pedal
3. R2D

## Control Systems

- [APPS](./apps.md)
- [Ready 2 Go (R2D)](./R2D.md)

## Custom Printed Circuit Boards (PCBs)

- [CustomNode Lite](.)

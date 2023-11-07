# Ready 2 Go (R2D)

Is your car ready to go?

## Requirements

For the Ready 2 Go Signal to be triggered the following conditions must be met:

- pre-charge completed
- brake AND start button engage simultaneously

## Proposed Structure

how will we be implementing this feature?

### Schematic

Following the principle of: `Each node serving only 1 purpose`

![rsc/r2d_proposed_structure.png](rsc/r2d_proposed_structure.png)

These are the key nodes in the R2D network.

1. R2D Brain
2. Starter (Start buttons x [tbd])
3. Buzzer
4. Brake* (if not already part of Starter)
5. Pre-Charge (quantity: however many required)

\* optional, depending on conditions

## Flow

1. triggered R2D conditions (...)
2. send R2D trigger to main Can Network
3. Check if stateMachine advertise car state as R2D
4. send buzzer trigger via R2D Can Network


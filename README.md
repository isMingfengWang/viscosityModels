# viscosityModels Guo



[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) 



## Guo model

The Guo model is a model used in cement rheology that developed by fitting experimental data. The model is
$$
\nu = \frac{\tau_0/\rho}{\gamma}\left(1+\alpha \gamma\right)^{\beta}
$$
where $\tau_0$ is the yield stress $[\mathrm{Pa}]$, $\rho$ is the fluid density $[\frac{\mathrm{kg}}{\mathrm{m^3}}]$,  $\gamma$ is the shear strain rate $[\frac{1}{\mathrm{s}}]$, $\alpha$ is an empirical parameter $[\mathrm{s}]$, and $\beta$ a dimensionless empirical parameter $[-]$.



## Compile Guo model

### Command Line

Compile this rheology after activating `OpenFOAM` environment using the following command line

```bash
wmake libso
```

## Support

For questions or further information, please reach out to me at mingfeng.wang@outlook.com